#ifndef _SUBSECTOR_H_
#define _SUBSECTOR_H_
#if defined(_MSC_VER)
#pragma once
#endif

/*! 
* \file subsector.h
* \ingroup CIAM
* \brief The subsector class header file.
* \author Sonny Kim
* \date $Date$
* \version $Revision$
*/

#include <vector>
#include <map>
#include <xercesc/dom/DOM.hpp>

// Forward declarations
class Summary;
class technology;
class hydro_tech;
class Emcoef_ind;

/*! 
* \ingroup CIAM
* \brief A class which defines a single Subsector of the model.

* The subsector contains a group of technology objects, which produce or consume commodities in the marketplace. Each sub-sector has attributes such as share, share weight, logit expoential, fixed capacity, and capacity limits. 

* \author Sonny Kim, Steve Smith, Josh Lurz
*/

class subsector
{
protected:
    std::string name; //!< subsector name
    std::string regionName; //!< region name
    std::string sectorName; //!< sector name
    std::string unit; //!< unit of final product from subsector
    std::string fueltype; //!< each subsector has one fueltype
    int notech; //!< number of technologies in each subsector
    double tax; //!< subsector tax or subsidy
    double basesharewt; //! subsector base year consumption share weight
    bool debugChecking; //!< General toggle to turn on various checks
    std::vector<std::vector<technology*> > techs; //!< array of pointers to technology objects for each period
    std::vector<hydro_tech> hydro; //!< array of hydroelectricity by period
    std::vector<double> capLimit; //!< subsector capacity limit
    std::vector<bool> capLimited; //!< true if subsector has hit its capacity limit
    std::vector<double> fixedShare; //!< share of this sub-sector that is fixed capacity -- set in sector
    std::vector<double> shrwts; //!< subsector logit share weights
    std::vector<double> lexp; //!< subsector logit exponential
    std::vector<double> share; //!< subsector shares
    std::vector<double> input; //!< subsector energy input
    std::vector<double> pe_cons; //!< subsector primary energy consumption
    std::vector<double> subsectorprice; //!< subsector price for all periods
    std::vector<double> fuelprice; //! subsector fuel price only for all periods
    std::vector<double> output; //!< total amount of final output from subsector
    std::vector<double> carbontaxpaid; //!< total subsector carbon taxes paid
    std::vector<double> fuelPrefElasticity; //!< Fuel preference elasticity
    std::vector<double> calOutputValue; // Calibration value
    std::vector<bool> doCalibration; // Flag set if calibration value is read-in
    std::vector<bool> calibrationStatus; // Set true if sector or any tech is calibrated
    std::vector<Summary> summary; //!< summary for reporting
    std::map<std::string,int> techNameMap; //!< Map of technology name to integer position in vector. 

    void shareWeightScale( const int pmer ); // Consistantly adjust share weights
    void sumOutput( const int period );
    
public:
    subsector();
    virtual ~subsector();
    virtual void clear();
    static double capLimitTransform( double capLimit, double orgShare ); 
    const std::string getName() const;
    void XMLParse( const xercesc::DOMNode* tempNode );
    virtual void XMLDerivedClassParse( const std::string nodeName, const xercesc::DOMNode* curr );
    void completeInit();
    void toXML( std::ostream& out ) const;
    virtual void toOutputXML( std::ostream& out ) const;
    void toDebugXML( const int period, std::ostream& out ) const;
    virtual void calcPrice( const std::string regionName, const int period);
    double getPrice( const int period ) const;
    void initCalc( const int per );
    bool getCalibrationStatus( const int period ) const;
    void setCalibrationStatus( const int period );
    void scaleCalibrationInput( const int period, const double scaleFactor );
    bool allOuputFixed( const int period ) const;
    double subsector::getFixedShare( const int per ) const;
    void subsector::setFixedShare( const int per, const double share );
    void subsector::setShareToFixedValue( const int per );
    double getfuelprice( const int period ) const; 
    double getwtfuelprice( const int period ) const;
    double getCapacityLimit( const int period ) const;
    void applycarbontax( const std::string& regionName, const double tax, const int period );
    void addghgtax( const std::string& ghgname, const std::string& regionName, const int period ); 
    virtual void calcShare( const std::string& regionName, const int period, const double gnp_cap = 1 ); 
    void shareWeightInterp( const int beginPeriod,  const int endPeriod );
    void setShare( const double shareVal, const int per );
    void normShare( const double sum, const int period );
    double getShare( const int period ) const;
    void limitShares( const double sum, const int period );
    void setCapLimitStatus( const bool value, const int period );
    bool getCapLimitStatus( const int period ) const;
    void calcTechShares ( const std::string& regionName, const int period );
    virtual void setoutput( const std::string& regionName, const std::string& prodName, const double dmd, const int period ); 
    double exogSupply( const int period );
    void scaleFixedSupply( const double scaleRatio, const int per );
    double getFixedSupply( const int per ) const;
    void resetFixedSupply( const int per );
    double getTotalCalOutputs( const int period ) const;
    void showtechs( const int period, const std::string ofile ) const;
    void showlabel( const std::string& ofile ) const;
    void outputfile( const std::string& regionName, const std::string& sectorName) const; 
    void MCoutputA( const std::string& regionName, const std::string& sectorName ) const; 
    void MCoutputB( const std::string& regionName, const std::string& sectorName ) const; 
    void MCoutputC( const std::string& regionName, const std::string& sectorName ) const; 
    int getNumberTech() const;
    void emission( const int period, const std::string& productName );
    void indemission( const int period, const std::vector<Emcoef_ind>& emcoef_ind );
    double showCO2( const int period ) const;
    double showCO2ind( const int period ) const;
    double showCO2fuel( const int period ) const;
     double getInput( const int period )  const;
    double getOutput( const int period );
    double getTotalCarbonTaxPaid( const int period ) const;
    std::map<std::string, double> getfuelcons( const int period ) const; 
    void clearfuelcons( const int period);
    std::map<std::string, double> getemission( const int period) const;
    std::map<std::string, double> getemfuelmap( const int period) const; 
    std::map<std::string, double> getemindmap( const int period ) const;
    void adjShares( const double dmd, const double shareRatio, const double totalFixedSupply, const int period);
    void updateSummary(const int per);
    void adjustForCalibration( double sectorDemand, double totalFixedSupply, double totalCalOutputs, const int period );
    void setRegionName(const std::string& regionNameIn );
    void setSectorName(const std::string& sectorNameIn );
};
#endif // _SUBSECTOR_H_
