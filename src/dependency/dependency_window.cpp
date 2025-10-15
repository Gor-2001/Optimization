/***************************************/
// dependency_window.cpp
/***************************************/
#include "dependency_window.h"
/***************************************/

DependencyWindow::DependencyWindow(QWidget *parent)
    : BaseWindow(parent)
{
    // Variables that may change during execution (mutable, e.g., loop/spine-related)
    const uint16_t runCount     = 1000;
    const uint16_t sampleSize   = 2048;
    const uint16_t sampleRange  = 256;

    setRunCount(runCount);
    setRunCountIndex(DEP_RUN_COUNT_INDEX);

    setSpinVariables({
        {"Run Count", runCount},
        {"Sample Size", sampleSize},
        {"Sample Range", sampleRange}
    });

    setParam(dependency_params);
    setInitFunction<dependency_params_t>(DependencyWindow::dependency_params_init);
    setGenFunction<dependency_params_t>(DependencyWindow::sample_gen);

    setTestFunctions<dependency_params_t>({
        {"DEPENDENT\t", DependencyWindow::test_neighbor_add},
        {"INDEPENDENT\t", DependencyWindow::test_halfway_add}
    });

    setInfoTitle("Dependency Test Info");
    setInfoPath("src/dependency/dependency_info");
    setRunTitle("Run Dependency Test");

    setupWindow();
}

void 
DependencyWindow::dependency_params_init(
    dependency_params_t& dependency_params, 
    const std::vector<uint16_t>& spinVariables
)
{
    dependency_params.sample_size = spinVariables[DEP_SAMPLE_SIZE_INDEX];
    dependency_params.sample_range = spinVariables[DEP_SAMPLE_RANGE_INDEX];
}

void 
DependencyWindow::sample_gen(
    dependency_params_t& dependency_params
)
{
    dependency_params.sample = 
        random_sample_generation16(dependency_params.sample_size, dependency_params.sample_range);
}

void 
DependencyWindow::test_neighbor_add(    
    dependency_params_t& dependency_params
)
{
    for (uint16_t i = 0; i < dependency_params.sample.size() - 1; i++)
        dependency_params.sample[i] = dependency_params.sample[i + 1];
    
    dependency_params.sample[dependency_params.sample.size() - 1] += dependency_params.sample[0];
}

void 
DependencyWindow::test_halfway_add(    
    dependency_params_t& dependency_params
)
{
    uint16_t size = dependency_params.sample.size() / 2;

    for (uint16_t i = 0; i < size; i++)
        dependency_params.sample[i]  += dependency_params.sample[size + i];

    
    for (uint16_t i = 0; i < size; i++)
        dependency_params.sample[size + i]  += dependency_params.sample[i];
}

