#include "vtkAlgorithmFilter.h"

#include "vtkCommand.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkObjectFactory.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkDataObject.h"

vtkCxxRevisionMacro(vtkAlgorithmFilter, "$Revision: 1.1 $");
vtkStandardNewMacro(vtkAlgorithmFilter);

//----------------------------------------------------------------------------
vtkAlgorithmFilter::vtkAlgorithmFilter()
{
  this->SetNumberOfInputPorts( 1 );
  this->SetNumberOfOutputPorts( 1 );
}

//----------------------------------------------------------------------------
int vtkAlgorithmFilter::FillOutputPortInformation(
    int vtkNotUsed(port), vtkInformation* info)
{
  // now add our info
  info->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkTest");
  return 1;
}

//----------------------------------------------------------------------------
int vtkAlgorithmFilter::FillInputPortInformation(
                                               int vtkNotUsed(port), vtkInformation* info)
{
  info->Set(vtkAlgorithm::INPUT_REQUIRED_DATA_TYPE(), "vtkTest");
  return 1;
}


int vtkAlgorithmFilter::RequestDataObject(vtkInformation* vtkNotUsed(request),
                                         vtkInformationVector** vtkNotUsed(inputVector),
         vtkInformationVector* outputVector )
{
//RequestDataObject (RDO) is an earlier pipeline pass.
//During RDO, each filter is supposed to produce an empty data object of the proper type
/*
  vtkInformation* outInfo = outputVector->GetInformationObject(0);
  vtkTest* output = vtkTest::SafeDownCast(
                                            outInfo->Get( vtkDataObject::DATA_OBJECT() ) );
  
  if ( ! output )
    {
    output = vtkTest::New();
    outInfo->Set( vtkDataObject::DATA_OBJECT(), output );
    output->FastDelete();
    output->SetPipelineInformation( outInfo );
    
    this->GetOutputPortInformation(0)->Set(
                                    vtkDataObject::DATA_EXTENT_TYPE(), output->GetExtentType() );
    }
*/
  return 1;
}


//----------------------------------------------------------------------------
int vtkAlgorithmFilter::ProcessRequest(vtkInformation* request,
                                     vtkInformationVector** inputVector,
                                     vtkInformationVector* outputVector)
{
  // Create an output object of the correct type.
  if(request->Has(vtkDemandDrivenPipeline::REQUEST_DATA_OBJECT()))
  {
    return this->RequestDataObject(request, inputVector, outputVector);
  }
  // generate the data
  if(request->Has(vtkDemandDrivenPipeline::REQUEST_DATA()))
  {
    return this->RequestData(request, inputVector, outputVector);
  }

  if(request->Has(vtkStreamingDemandDrivenPipeline::REQUEST_UPDATE_EXTENT()))
  {
    return this->RequestUpdateExtent(request, inputVector, outputVector);
  }

  // execute information
  if(request->Has(vtkDemandDrivenPipeline::REQUEST_INFORMATION()))
  {
    return this->RequestInformation(request, inputVector, outputVector);
  }

  return this->Superclass::ProcessRequest(request, inputVector, outputVector);
}


int vtkAlgorithmFilter::RequestInformation(
                                         vtkInformation* vtkNotUsed(request),
    vtkInformationVector** vtkNotUsed(inputVector),
                                      vtkInformationVector* vtkNotUsed(outputVector))
{
  // do nothing let subclasses handle it
  return 1;
}

int vtkAlgorithmFilter::RequestUpdateExtent(
                                          vtkInformation* vtkNotUsed(request),
    vtkInformationVector** inputVector,
    vtkInformationVector* vtkNotUsed(outputVector))
{
  int numInputPorts = this->GetNumberOfInputPorts();
  for (int i=0; i<numInputPorts; i++)
  {
    int numInputConnections = this->GetNumberOfInputConnections(i);
    for (int j=0; j<numInputConnections; j++)
    {
      vtkInformation* inputInfo = inputVector[i]->GetInformationObject(j);
      inputInfo->Set(vtkStreamingDemandDrivenPipeline::EXACT_EXTENT(), 1);
    }
  }
  return 1;
}


int vtkAlgorithmFilter::RequestData(
                                  vtkInformation* vtkNotUsed(request),
    vtkInformationVector **inputVector,
    vtkInformationVector* outputVector )
{
  //Later on RequestData (RD) happens.
//During RD each filter examines any inputs it has, then fills in that empty data object with real data.
/*
  vtkInformation* outInfo = outputVector->GetInformationObject(0);
  vtkTest* output = vtkTest::SafeDownCast(
                                          outInfo->Get( vtkDataObject::DATA_OBJECT() ) );
    
  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
  vtkTest *input = vtkTest::SafeDownCast(
                                         inInfo->Get(vtkDataObject::DATA_OBJECT()));
  output->ShallowCopy(input);
  output->SetValue(output->GetValue() + 1.0);
    */
  return 1;
}