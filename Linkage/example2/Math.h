#pragma once

#define DLLEXPORT __declspec(dllexport)

DLLEXPORT
void CheckGravity(std::string);

DLLEXPORT
void AddToGravity(double);

DLLEXPORT
void CheckSecrets();

DLLEXPORT
void CheckMoarSecrets();
