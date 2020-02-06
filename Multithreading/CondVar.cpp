/*

  Always use Condition Variables with Predicate, preferably atomic.
  https://www.modernescpp.com/index.php/c-core-guidelines-be-aware-of-the-traps-of-condition-variables
    - Better to use Condition Variables vs Atomics for threads that check so thread only runs when
      Condition Variable is set to appropriate value (vs all the time)

  Atomic Booleans
  https://www.modernescpp.com/index.php/the-atomic-boolean
*/


#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <memory>
#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>

class Monitoring;

class Monitoring
{
    std::thread MonitoringWatchThread;

    std::thread GcsChecker;
    std::mutex GcsMutex;
    std::condition_variable GcsCondVar;
    std::atomic<bool> GcsReady;

    std::thread ApPkiChecker;
    std::mutex ApPkiMutex;
    std::condition_variable ApPkiCondVar;
    std::atomic<bool> ApPkiReady;

    std::map<std::string, std::string> EnvVars;
    std::string ObjectName;

    static
    void WatchThread(Monitoring* object);

public:
    Monitoring()
    {
        ObjectName = "Default";
        GcsReady = false;
        ApPkiReady = false;
    }

    ~Monitoring() {}

    void Initialize();
    void Terminate()
    {
        
    }

    std::string GetName()
    {
        return ObjectName;
    }

    // Fabric calls this
    static
    void MockSetGcsData(Monitoring* object)
    {
        object->GcsReady = true;
        std::cout << "Gcs Config File was updated!\n";
        object->GcsCondVar.notify_one();

        return;
    }

    static
    void MockApPkiAvailable();

};

void
Monitoring::Initialize()
{
    std::cout << "Initializing object name: " << this->ObjectName << '\n';
    std::thread MonitoringWatchThread(WatchThread, this);

    // Detach to allow WatchThread to continue to run when this scope terminates
    MonitoringWatchThread.detach();

    //std::thread Mcf(Monitoring::MockSetMcfData, this);

    //MonitoringWatchThread.join(); // Hang here forever

    return;
}

void
Monitoring::WatchThread(Monitoring* object)
{
    bool useLocalConfig { false };

    std::cout << "Starting WatchThread on object name: " << object->GetName() << '\n';

    while (true)
    {
        std::cout << "Beginning of loop\n";

        // Check if we want to stop

        // Wait for 20 seconds
        std::this_thread::sleep_for(std::chrono::seconds(2));

        // Check if we want to stop

        // std::cout  << "Waiting for Mcf Data to be ready...\n";
        // std::unique_lock<std::mutex> McfLock(object->McfMutex);
        // object->McfCondVar.wait(McfLock, [object]{ return object->McfReady.load(); });
        // std::cout << "Mcf Data is ready, proceeding...\n";

        // Wait for GCS Config which implicitly waits for MCF Data
        std::cout << "Waiting for GCS Config File\n";
        {
            std::unique_lock<std::mutex> GcsLock(object->GcsMutex);
            object->GcsCondVar.wait(GcsLock, [object]{ return object->GcsReady.load(); });
            std::cout << "Gcs Config File is ready, proceeding\n";
        }


        //break;
    }

    return;
}

int main()
{
    Monitoring AgentMonitor;
    AgentMonitor.Initialize();

    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::thread GcsThread(Monitoring::MockSetGcsData, &AgentMonitor);
    GcsThread.join();

    return 0;
}
