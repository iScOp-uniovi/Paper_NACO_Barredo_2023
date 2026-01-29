cmake_minimum_required(VERSION 3.16)
project(ag_workflow)

set(CMAKE_CXX_STANDARD 14)

SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -O3")

include_directories(.)
set(SOURCE_FILES ga/AlgoritmoGenetico.h
        chromosome/cromosoma.h
        tools/crono.cpp
        tools/crono.h
        chromosome/crPermuta.h
        selection_replacement/escalado.h
        selection_replacement/escCte.h
        selection_replacement/escMattfeld.h
        tools/excepcion.h
        ga/genPermuta.cpp
        ga/genPermuta.h
        main.cpp
        crossover/opCruce.h
        crossover/opCruGPX.cpp
        crossover/opCruGPX.h
        operador.h
        fitness/opFitness.h
        fitness/opFitnessBL.h
        fitness/opFitOrden.cpp
        fitness/opFitOrden.h
        generation/opGenesis.h
        generation/opGenPermuta.cpp
        generation/opGenPermuta.h
        mutation/opMutacion.h
        mutation/opMutAleatorio.cpp
        mutation/opMutAleatorio.h
        mutation/opMutSimple1.cpp
        mutation/opMutSimple1.h
        mutation/opMutSimple2.cpp
        mutation/opMutSimple2.h
        selection_replacement/opSeleccion.h
        selection_replacement/opSelRuleta.h
        selection_replacement/opSelTorneo.h
        poblacion.h
        problem/problema.cpp
        problem/problema.h
        problem/proPermuta.cpp
        problem/proPermuta.h
        tools/random.cpp
        tools/random.h
        tools/traza.h
        problem/host_parser.h
        problem/host_parser.cpp
        problem/workflow_parser.h
        problem/workflow_parser.cpp
        tools/unit_parser.h
        tools/unit_parser.cpp
        fitness/heft_service.cpp
        fitness/heft_service.h
        fitness/opFitOrdenPlus.h
        fitness/opFitOrdenPlus.cpp chromosome/cromosoma.cpp)

find_package(nlohmann_json CONFIG REQUIRED)
add_executable(ag_workflow ${SOURCE_FILES})


