// Copyright (C) 2015 - IIT Bombay - FOSSEE
//
// Author: Harpreet Singh
// Organization: FOSSEE, IIT Bombay
// Email: harpreet.mertia@gmail.com
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

function [xopt,fopt,iter] = symphony (varargin)

  // Solves a linearily constrained optimization problem.
  //
  // Calling Sequence
  //   x = symphony(nbVar,nbCon,objCoef,isInt,LB,UB,conMatrix,conLB,conUB)
  //   x = symphony(nbVar,nbCon,objCoef,isInt,LB,UB,conMatrix,conLB,conUB,objSense)
  //   x = symphony(nbVar,nbCon,objCoef,isInt,LB,UB,conMatrix,conLB,conUB,objSense,options)
  //   [xopt,fopt,status,iter] = symphony( ... )

//To check the number of input and output argument
   [lhs , rhs] = argn();
	
//To check the number of argument given by user
   if ( rhs < 9 | rhs > 11 ) then
    errmsg = msprintf(gettext("%s: Unexpected number of input arguments : %d provided while should be in the set [9 10 11]"), "Symphony", rhs);
    error(errmsg)
   end
   
   nbVar = varargin(1);
   nbCon = varargin(2);
   objCoef = varargin(3);
   isInt = varargin(4);
   LB = varargin(5);
   UB = varargin(6);
   conMatrix = varargin(7);
   conLB = varargin(8);
   conUB = varargin(9);
   
   if ( rhs<10 ) then
      objSense = 1;
   else
      objSense = varargin(10);
   end
   
   if (rhs<11) then
      options = [];
   else
      options = varargin(11);
   end
   

//Check the size of Lower Bound which should equal to the number of variables
   if ( size(LB) ~= nbVar) then
      errmsg = msprintf(gettext("%s: The Lower Bound is not equal to the number of variables"), "Symphony");
      error(errmsg);
   end

//Check the size of Upper Bound which should equal to the number of variables
   if ( size(UB) ~= nbVar) then
      errmsg = msprintf(gettext("%s: The Upper Bound is not equal to the number of variables"), "Symphony");
      error(errmsg);
   end

//Check the size of Lower Bound which should equal to the number of constraints
   if ( size(conLB) ~= nbCon) then
      errmsg = msprintf(gettext("%s: The Lower Bound of constraints is not equal to the number of constraints"), "Symphony");
      error(errmsg);
   end

//Check the size of Upper Bound which should equal to the number of constraints
   if ( size(conUB) ~= nbCon) then
      errmsg = msprintf(gettext("%s: The Upper Bound of constraints is not equal to the number of constraints"), "Symphony");
      error(errmsg);
   end

   [xopt,fopt,iter] = symphony_call(nbVar,nbCon,objCoef,isInt,LB,UB,conMatrix,conLB,conUB,objSense,options);

endfunction
