## 📄 Description
This repository contains supplementary material for the paper:

> "**Precise makespan optimization via hybrid genetic algorithm for scientific workflow scheduling problem**"  
> Published in **Natural Computing (NACO)**  
> Authors: Pablo Barredo, Jorge Puente  
> Paper (RUO): https://hdl.handle.net/10651/70610  

Task scheduling in scientific workflows is an NP-hard problem due to the large number of interdependent tasks, the data transfers between them, and the diversity of possible execution infrastructures in cloud environments. Makespan is one of the main optimisation objectives, but its estimation must also be reliable with respect to the actual execution time to avoid unexpected costs in pay-per-use scenarios.

This work extends a disk-network-computing (DNC) evaluation model that explicitly accounts for storage-related communications, and integrates it into a genetic algorithm and the well-known HEFT heuristic. Several hybrid metaheuristics are proposed, together with an accuracy metric to measure the similarity between estimated and real makespans. The experimental results show that the DNC-based model improves the accuracy of makespan estimations with respect to the standard network-computing model, and that the hybrid approaches significantly improve the makespan in heterogeneous cloud infrastructures.

* * *

## Repository Content

This repository provides the software prototype and lightweight reference material
associated with the experimental evaluation reported in the paper.

- `code/` → Implementation of the proposed algorithm(s) and hybrid approaches.
- `data/` → Dataset used in the experiments and the scripts and configuration files needed to repeat them.
- `results/` → Outcomes obtained after running the experiments.

* * *

## Data availability (RUO)

The **authoritative and citable archive** of the data associated with this work
(instances, configurations and experimental results, including interoperable CSV exports
and detailed documentation) is available in the University of Oviedo Institutional
Repository (RUO):

https://hdl.handle.net/10651/81943

The materials included in this GitHub repository are provided to facilitate
understanding and computational reproducibility, but the RUO dataset should be considered
the reference version for reuse and citation.

---

## Datasets and code

The datasets and code provided in this repository aim to facilitate the understanding
and reproducibility of the experiments presented in the paper.  
The authoritative and citable archive of the data and experimental results is the dataset
deposited in RUO (see link above).

The C++ research prototype implementing the genetic and hybrid algorithms evaluated in the
paper is available under the `code/ag-workflow/` directory. Detailed build and usage
instructions are provided in its corresponding README file.

---

## Using the Material

To access and utilize the supplementary material, clone this repository and navigate to the appropriate directories:

```bash
git clone https://github.com/iScOp-uniovi/Paper_NACO_Barredo_2023
cd Paper_NACO_Barredo_2023
```


Follow the guidelines in each subdirectory to run the code and analyze the data.

---

## 🔍 Cite this Work

If you use this material in your research, please cite our paper as follows:
```
@article{Barredo2023NACO,
  author  = {Barredo, Pablo and Puente, Jorge},
  title   = {Precise makespan optimization via hybrid genetic algorithm for scientific workflow scheduling problem},
  journal = {Natural Computing},
  year    = {2023},
  volume  = {22},
  pages   = {615--630},
  doi     = {10.1007/s11047-023-09950-5}
}
```

---
## License

- All **datasets and experimental results** associated with this work are released under
  the **Open Data Commons Attribution License (ODC-By)**, as specified in the dataset record
  in RUO.

- Documentation files (including this README) are released under the  
  **Creative Commons Attribution 4.0 International License (CC BY 4.0)**.

- All **source code** contained in the `code/` directory is released under the  
  **MIT License** (see `code/ag-workflow/LICENSE`).

---

## 📧 Contact
For any questions or inquiries about this work, please contact the corresponding author:
✉️ **[puente@uniovi.es](mailto:puente@uniovi.es)**

