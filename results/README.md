# Precise Makespan Optimization via Hybrid Genetic Algorithm for Scientific Workflow Scheduling Problem

The files contain all the data gathered in the experimentation.

The information is separated in two files (in Microsoft Excel format: .xlsx):
- `benchmark_analysis_fast.V3`
- `benchmark_analysis_mixed.V3`

## Description of the contents

Both excels contains the same distribution, but one is for the scenario with the same type of host and the other is for the mixed scenario.

### Instances tab
Contains the name off all instances used in the experimentation.

### Data tab
In this tab we can find the raw data. Each row is the execution for a benchmark and a host. The Real value means the Makespan is from the wrench simulator. The calculated Makespan is from the GA. The other fields are used to calculate the dynamic tables.

### Accuracy Tab
This dynamic table contains the accuracy study.  The second table is calculated using the min value for each instance and then calculating the mean of those values per problem family.

### Makespan MPE
This dynamic table contains the MPE study. The values in bold are when there is an improvement from the base makespan ($HEFT_{NC}$)


