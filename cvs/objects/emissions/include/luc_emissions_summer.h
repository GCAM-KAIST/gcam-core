#ifndef _LUC_EMISSIONS_SUMMER_H_
#define _LUC_EMISSIONS_SUMMER_H_
#if defined(_MSC_VER)
#pragma once
#endif

/*
* LEGAL NOTICE
* This computer software was prepared by Battelle Memorial Institute,
* hereinafter the Contractor, under Contract No. DE-AC05-76RL0 1830
* with the Department of Energy (DOE). NEITHER THE GOVERNMENT NOR THE
* CONTRACTOR MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR ASSUMES ANY
* LIABILITY FOR THE USE OF THIS SOFTWARE. This notice including this
* sentence must appear on any copies of this computer software.
* 
* EXPORT CONTROL
* User agrees that the Software will not be shipped, transferred or
* exported into any country or used in any manner prohibited by the
* United States Export Administration Act or any other applicable
* export laws, restrictions or regulations (collectively the "Export Laws").
* Export of the Software may require some form of license or other
* authority from the U.S. Government, and failure to obtain such
* export control license may result in criminal liability under
* U.S. laws. In addition, if the Software is identified as export controlled
* items under the Export Laws, User represents and warrants that User
* is not a citizen, or otherwise located within, an embargoed nation
* (including without limitation Iran, Syria, Sudan, Cuba, and North Korea)
*     and that User is not otherwise prohibited
* under the Export Laws from receiving the Software.
* 
* Copyright 2011 Battelle Memorial Institute.  All Rights Reserved.
* Distributed as open-source under the terms of the Educational Community 
* License version 2.0 (ECL 2.0). http://www.opensource.org/licenses/ecl2.php
* 
* For further details, see: http://www.globalchange.umd.edu/models/gcam/
*
*/


/*! 
* \file luc_emissions_summer.h
* \ingroup Objects
* \brief LUCEmissionsSummer class header file.
* \author Kate Calvin
*/

#include "util/base/include/time_vector.h"
#include "util/base/include/default_visitor.h"
#include "util/base/include/value.h"

/*! 
* \ingroup Objects
* \brief A class which sums emissions for a particular gas.
* \details 
* \author Josh Lurz
*/

class LUCEmissionsSummer : public DefaultVisitor {
public:
    explicit LUCEmissionsSummer( const std::string& aGHGName );

    virtual void startVisitCarbonCalc( const ICarbonCalc* aCarbonCalc,
                                       const int aPeriod );

    // Non-IVisitor interface methods.
    double getEmissions( const int aYear ) const;
    
    double getEmissionsPositive( const int aYear ) const;
    
    double getEmissionsNegative( const int aYear ) const;

    double areEmissionsSet( const int aYear ) const;
private:
    //! The name of the GHG being summed.
    const std::string mGHGName;

    //! The gross positive above ground LUC emissions
    objects::YearVector<Value> mPositiveEmissionsByYear;
    
    //! The gross negative above ground LUC *emissions* (i.e. uptake however values contained are  < 0)
    objects::YearVector<Value> mNegativeEmissionsByYear;
    
    // The net below ground LUC emissions
    objects::YearVector<Value> mBelowTotalEmissionsByYear;
};

#endif // _LUC_EMISSIONS_SUMMER_H_
