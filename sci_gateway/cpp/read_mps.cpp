// Copyright (C) 2015 - IIT Bombay - FOSSEE
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// Author: Guru Pradeep Reddy Bhanu Priya Sayal
// Organization: FOSSEE, IIT Bombay
// Email: toolbox@scilab.in

#include "sci_iofunc.hpp"
#include "OsiClpSolverInterface.hpp"

extern "C"{
#include <api_scilab.h>
#include <Scierror.h>
#include <localization.h>
#include <sciprint.h>
#include <iostream>

//Solver function
int sci_rmps(char *fname) 
{
    //creating a problem pointer using base class of OsiSolverInterface and
    //instantiate the object using derived class of ClpSolverInterface
    OsiSolverInterface* si = new OsiClpSolverInterface();

    // Error management variable
	SciErr sciErr;

	//data declarations
	int *piAddressVarOne = NULL;                 //pointer used to access argument of the function
	char* ptr;                              	 //pointer to point to address of file name
    double* options_;                            //options to set maximum iterations 
	CheckInputArgument(pvApiCtx, 2,2 );          //Check we have exactly two arguments as input or not
	CheckOutputArgument(pvApiCtx, 6, 6);         //Check we have exactly six arguments on output side or not
    //Getting the input arguments from Scilab
    //Getting the MPS file path
	//Reading mps file
	getStringFromScilab(1,&ptr);

 	std::cout<<ptr;
	
    //get options from Scilab
    if(getFixedSizeDoubleMatrixInList(2 , 2 , 1 , 1 , &options_))
	{
		return 1;
	}

    //Read the MPS file
    si->readMps(ptr);

    //setting options for maximum iterations
    si->setIntParam(OsiMaxNumIteration,options_[0]);

    //Solve the problem
    si->initialSolve();
  
    //Quering about the problem
    //get number of variables
    double numVars_;
    numVars_ = si->getNumCols();
  
    //get number of constraint equations
    double numCons_;
    numCons_ = si->getNumRows();
   
    //Output the solution to Scilab
    //get solution for x	//const r
    const double* xValue = si->getColSolution();
   
    //get objective value
    double objValue = si->getObjValue();

    //get Status value
    double status;
    if(si->isProvenOptimal())
    	status=0;
    else if(si->isProvenPrimalInfeasible())
    	status=1;
    else if(si->isProvenDualInfeasible())
        status=2;
    else if(si->isIterationLimitReached())
        status=3;
   	else if(si->isAbandoned())
        status=4;
   	else if(si->isPrimalObjectiveLimitReached())
        status=5;
   	else if(si->isDualObjectiveLimitReached())
        status=6;

    //get number of iterations
    double iterations = si->getIterationCount();

    //get reduced cost	//const r
    const double* reducedCost = si->getReducedCost();
   
    //get dual vector //const r	
    const double* dual = si->getRowPrice();
  
    returnDoubleMatrixToScilab(1 , 1 , numVars_ , xValue);
    returnDoubleMatrixToScilab(2 , 1 , 1 , &objValue);
    returnDoubleMatrixToScilab(3 , 1 , 1 , &status);
    returnDoubleMatrixToScilab(4 , 1 , 1 , &iterations);
    returnDoubleMatrixToScilab(5 , 1 , numVars_ , reducedCost);
    returnDoubleMatrixToScilab(6 , 1 , numCons_ , dual);
	
	free((double *)xValue);
	free((double *)dual);
	free((double *)reducedCost);
  }
}
