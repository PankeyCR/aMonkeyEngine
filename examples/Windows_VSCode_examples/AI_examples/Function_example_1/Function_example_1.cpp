
#define ame_Windows

#include "aMonkeyEngine/System.hpp"
#include "aMonkeyEngine/PrimitiveList.hpp"
#include "aMonkeyEngine/PrintableList.hpp"

#include "aMonkeyEngine/Function.hpp"
#include "aMonkeyEngine/LearningData.hpp"
#include "aMonkeyEngine/FunctionTrainer.hpp"
#include "aMonkeyEngine/FunctionConfiguration.hpp"


using namespace ame;

int main(){

    Random<float> i_random = new AbsoluteRandom();

    LearningData<float> i_metric_1;
    i_metric_1.random(i_random);
    i_metric_1.epochs(1000);
    i_metric_1.error(0.01f);
    i_metric_1.inputs(15);
    i_metric_1.output(3);

    LearningData<float> i_metric_2;
    i_metric_2.random(i_random);
    i_metric_2.epochs(1000);
    i_metric_2.error(0.01f);
    i_metric_2.inputs(10);
    i_metric_2.output(25);

    PrimitiveList<LearningData<float>> i_metrics;
    i_metrics.add(i_metric_1);
    i_metrics.add(i_metric_2);

    Trainer<Function<float>> i_trainer = new RandomTrainer<Function<float>>();
    Tester<Function<float>,PrimitiveList<float>> i_tester = new FunctionTester<float>();

    AiCreator<Function<float>> i_creator;

    Function<float>* i_function = i_creator.create(i_metrics, i_trainer);

    PrimitiveList<float> i_test_result = i_creator.test(i_metrics, i_function, i_tester);
    
    System::console.println("result: ");
    System::console.println(PrintableList<PrimitiveList<float>,float>(i_test_result));

    delete i_function;

    return 0;
}



//