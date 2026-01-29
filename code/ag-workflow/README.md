# ag-workflow (C++ research prototype)

## Overview
This directory contains the C++ prototype of the Genetic Algorithm used in the experiments
reported in the associated NACO 2023 publication. The goal of this release is **computational
reproducibility** and long-term availability, rather than production-grade packaging.

## Associated publication (RUO)
Paper record (RUO): https://hdl.handle.net/10651/70610

## Data and results (RUO)
The authoritative archive of workflow instances, host configurations and experimental results
is provided as an open dataset in RUO (to be filled once deposited):
- Dataset handle: https://hdl.handle.net/10651/81943

This GitHub repository hosts the prototype implementation and lightweight example inputs.

## Requirements
- C++17 compiler (GCC/Clang/MSVC)
- CMake >= 3.16
- Dependency: nlohmann/json (CMake package `nlohmann_json`)

## Build (out-of-source)
From the repository root:

```bash
cmake -S code/ag-workflow -B build/ag-workflow -DCMAKE_BUILD_TYPE=Release
cmake --build build/ag-workflow -j
```

## Run (smoke test)
A minimal example configuration is provided:

```bash
./build/ag-workflow/ag_workflow code/ag-workflow/config/entrada_gen.example.txt
```

Notes:
- The program reads parameters from a text configuration file.
- File paths inside the configuration file are interpreted relative to the **current working directory**.

## Repository hygiene
This repository does **not** store compiled binaries or build directories.
Please build using an out-of-source `build/` folder.


## Data availability (RUO)

This prototype is linked to the authoritative open dataset archived in RUO:

- Dataset handle: https://hdl.handle.net/10651/81943
