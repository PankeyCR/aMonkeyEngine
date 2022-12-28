
#define ame_ArduinoIDE 

#include "Application.hpp"
#include "DefaultApplication.hpp"
#include "TestRunnerState.hpp"
#include "TR_Full_List_Testing.hpp"
#include "TR_List_Reorder_Testing.hpp"
#include "TR_LinkedList_Testing.hpp"
#include "TR_Random_Testing.hpp"
#include "TR_Array_Testing.hpp"
#include "TR_Array2D_Testing.hpp"
#include "TR_Note_Testing.hpp"
#include "TR_ByteArray_Testing.hpp"
//#include "TR_Lexer_Testing.hpp"
#include "TR_DataNetwork_Testing.hpp"
//#include "TR_Set_Testing.hpp"
//#include "TR_Text_Exporter_Importer_Testing.hpp"
//#include "TR_Json_Exporter_Importer_Testing.hpp"
#include "TR_Vector2f_Testing.hpp"
#include "TR_Vector3f_Testing.hpp"
#include "TR_Vector4f_Testing.hpp"
#include "TR_Matrix3f_Testing.hpp"
#include "TR_Matrix4f_Testing.hpp"
#include "TR_Quaternion_Testing.hpp"
#include "System.hpp"
#include "MemoryRam.hpp"

using namespace ame;

Application* app;
TestRunnerState* testRunner;

void setup() {
  Serial.begin(9600);

  app = new DefaultApplication();

  testRunner = app->getStateManager()->addState(new TestRunnerState());
  testRunner->addUnitTest("Full_List_Testing", TR_Full_List_Testing);
  testRunner->addUnitTest("List_Reorder_Testing", TR_List_Reorder_Testing);
  testRunner->addUnitTest("LinkedList_Testing", TR_LinkedList_Testing);
  testRunner->addUnitTest("Random_Testing", TR_Random_Testing);
  testRunner->addUnitTest("Array_Testing", TR_Array_Testing);
  testRunner->addUnitTest("Array2D_Testing", TR_Array2D_Testing);
  testRunner->addUnitTest("Note_Testing", TR_Note_Testing);
  testRunner->addUnitTest("ByteArray_Testing", TR_ByteArray_Testing);
//  testRunner->addUnitTest("Lexer_Testing", TR_Lexer_Testing);
  testRunner->addUnitTest("DataNetwork_Testing", TR_DataNetwork_Testing);
//  testRunner->addUnitTest("Set_Testing", TR_Set_Testing);
//  testRunner->addUnitTest("Text_Exporter_Importer_Testing", TR_Text_Exporter_Importer_Testing);
//  testRunner->addUnitTest("Json_Exporter_Importer_Testing", TR_Json_Exporter_Importer_Testing);
  testRunner->addUnitTest("Vector2f_Testing", TR_Vector2f_Testing);
  testRunner->addUnitTest("Vector3f_Testing", TR_Vector3f_Testing);
  testRunner->addUnitTest("Vector4f_Testing", TR_Vector4f_Testing);
  testRunner->addUnitTest("Matrix3f_Testing", TR_Matrix3f_Testing);
  testRunner->addUnitTest("Matrix4f_Testing", TR_Matrix4f_Testing);
  testRunner->addUnitTest("Quaternion_Testing", TR_Quaternion_Testing);
}

void loop() {
  app->update();
  delay(3000);
  System::console.println("Stating Test");
  testRunner->runTest();
  System::console.println(getRamSize());
}






  





//