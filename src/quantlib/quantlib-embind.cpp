#include <emscripten/bind.h>
#include <malloc.h>
#include <iostream>
#include <iomanip>
#include <string>
#include "json.hpp"

#include "ql/qldefines.hpp"
#include <boost/config.hpp>
#ifdef BOOST_MSVC
#include <ql/auto_link.hpp>
#endif

/*Amoritazation*/
#include <ql/instruments/bonds/zerocouponbond.hpp>
#include <ql/instruments/bonds/floatingratebond.hpp>
#include <ql/pricingengines/bond/discountingbondengine.hpp>
#include <ql/cashflows/couponpricer.hpp>
#include <ql/termstructures/yield/piecewiseyieldcurve.hpp>
#include <ql/termstructures/yield/bondhelpers.hpp>
#include <ql/termstructures/volatility/optionlet/constantoptionletvol.hpp>
#include <ql/indexes/ibor/euribor.hpp>
#include <ql/indexes/ibor/usdlibor.hpp>
#include <ql/time/calendars/target.hpp>
#include <ql/time/calendars/unitedstates.hpp>
#include <ql/time/daycounters/actualactual.hpp>
#include <ql/time/daycounters/actual360.hpp>
#include <ql/time/daycounters/thirty360.hpp>
#include <ql/time/calendars/israel.hpp>
 
#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>

/*CVAIRS*/
#include <ql/indexes/ibor/euribor.hpp>
#include <ql/instruments/makevanillaswap.hpp>
#include <ql/instruments/vanillaswap.hpp>
#include <ql/pricingengines/swap/cvaswapengine.hpp>
#include <ql/pricingengines/swap/discountingswapengine.hpp>
#include <ql/termstructures/credit/interpolatedhazardratecurve.hpp>
#include <ql/termstructures/yield/piecewiseyieldcurve.hpp>
#include <ql/termstructures/yield/ratehelpers.hpp>
#include <ql/time/calendars/target.hpp>
#include <ql/time/daycounters/actual360.hpp>
#include <ql/time/daycounters/actualactual.hpp>
/*end CVAIRS*/

/*Bonds*/
#include <ql/cashflows/couponpricer.hpp>
#include <ql/indexes/ibor/euribor.hpp>
#include <ql/indexes/ibor/usdlibor.hpp>
#include <ql/instruments/bonds/floatingratebond.hpp>
#include <ql/instruments/bonds/zerocouponbond.hpp>
#include <ql/pricingengines/bond/discountingbondengine.hpp>
#include <ql/termstructures/volatility/optionlet/constantoptionletvol.hpp>
#include <ql/termstructures/yield/bondhelpers.hpp>
#include <ql/termstructures/yield/piecewiseyieldcurve.hpp>
#include <ql/time/calendars/target.hpp>
#include <ql/time/calendars/unitedstates.hpp>
#include <ql/time/daycounters/actual360.hpp>
#include <ql/time/daycounters/actualactual.hpp>
#include <ql/time/daycounters/thirty360.hpp>
#include <ql/utilities/dataparsers.hpp>
/*end Bonds */

/*Convertible Bonds */
#include <ql/experimental/convertiblebonds/binomialconvertibleengine.hpp>
#include <ql/experimental/convertiblebonds/convertiblebond.hpp>
#include <ql/time/calendars/target.hpp>
#include <ql/time/daycounters/thirty360.hpp>
#include <ql/utilities/dataformatters.hpp>
#define LENGTH(a) (sizeof(a) / sizeof(a[0]))
/* end Convertible Bonds */

/*BermudanSwaptions*/
#include <ql/cashflows/coupon.hpp>
#include <ql/indexes/ibor/euribor.hpp>
#include <ql/instruments/swaption.hpp>
#include <ql/math/optimization/levenbergmarquardt.hpp>
#include <ql/models/shortrate/calibrationhelpers/swaptionhelper.hpp>
#include <ql/models/shortrate/onefactormodels/blackkarasinski.hpp>
#include <ql/pricingengines/swap/discountingswapengine.hpp>
#include <ql/pricingengines/swaption/fdg2swaptionengine.hpp>
#include <ql/pricingengines/swaption/fdhullwhiteswaptionengine.hpp>
#include <ql/pricingengines/swaption/g2swaptionengine.hpp>
#include <ql/pricingengines/swaption/jamshidianswaptionengine.hpp>
#include <ql/pricingengines/swaption/treeswaptionengine.hpp>
#include <ql/quotes/simplequote.hpp>
#include <ql/termstructures/yield/flatforward.hpp>
#include <ql/time/calendars/target.hpp>
#include <ql/time/daycounters/thirty360.hpp>
#include <ql/utilities/dataformatters.hpp>
/*end BermudanSwaptions*/

/*Callable Bonds */
#include <ql/experimental/callablebonds/callablebond.hpp>
#include <ql/experimental/callablebonds/treecallablebondengine.hpp>
#include <ql/models/shortrate/onefactormodels/hullwhite.hpp>
#include <ql/termstructures/yield/flatforward.hpp>
#include <ql/time/calendars/unitedstates.hpp>
#include <ql/time/daycounters/actualactual.hpp>
#include <cmath>
#include <vector>
/* end of Callable Bonds */

/*Options*/
#include <ql/instruments/vanillaoption.hpp>
#include <ql/pricingengines/vanilla/binomialengine.hpp>
#include <ql/pricingengines/vanilla/analyticeuropeanengine.hpp>
#include <ql/pricingengines/vanilla/analytichestonengine.hpp>
#include <ql/pricingengines/vanilla/baroneadesiwhaleyengine.hpp>
#include <ql/pricingengines/vanilla/bjerksundstenslandengine.hpp>
#include <ql/pricingengines/vanilla/batesengine.hpp>
#include <ql/pricingengines/vanilla/integralengine.hpp>
#include <ql/pricingengines/vanilla/fdblackscholesvanillaengine.hpp>
#include <ql/pricingengines/vanilla/mceuropeanengine.hpp>
#include <ql/pricingengines/vanilla/mcamericanengine.hpp>
#include <ql/pricingengines/vanilla/analyticeuropeanvasicekengine.hpp>
#include <ql/time/calendars/target.hpp>
#include <ql/utilities/dataformatters.hpp>
#include <ql/models/shortrate/onefactormodels/vasicek.hpp>
/*end of options*/

using namespace std;
using namespace QuantLib;
using namespace emscripten;
using json = nlohmann::json;

namespace
{

    ext::shared_ptr<YieldTermStructure> flatRate(const Date &today,
                                                 const ext::shared_ptr<Quote> &forward,
                                                 const DayCounter &dc,
                                                 const Compounding &compounding,
                                                 const Frequency &frequency)
    {
        return ext::shared_ptr<YieldTermStructure>(
            new FlatForward(today, Handle<Quote>(forward), dc, compounding, frequency));
    }

    ext::shared_ptr<YieldTermStructure> flatRate(const Date &today,
                                                 Rate forward,
                                                 const DayCounter &dc,
                                                 const Compounding &compounding,
                                                 const Frequency &frequency)
    {
        return flatRate(today, ext::shared_ptr<Quote>(new SimpleQuote(forward)), dc, compounding,
                        frequency);
    }

    std::string calculateCallableBonds(std::string data)
    {

        try
        {
            json jData = json::parse(data);

            Date today = Date(DateParser::parseISO(jData["request"]["referenceDate"].get<std::string>()));
            Settings::instance().evaluationDate() = today;

            Rate bbCurveRate = jData["request"]["bbCurveRate"].get<float>();

            DayCounter bbDayCounter = ActualActual(ActualActual::Bond);
            InterestRate bbIR(bbCurveRate, bbDayCounter, Compounded, Semiannual);

            Handle<YieldTermStructure> termStructure(
                flatRate(today, bbIR.rate(), bbIR.dayCounter(), bbIR.compounding(), bbIR.frequency()));

            CallabilitySchedule callSchedule;
            Real callPrice = jData["request"]["callPrice"].get<int>();
            Size numberOfCallDates = jData["request"]["numberOfCallDates"].get<int>();
            Date callDate = Date(DateParser::parseISO(jData["request"]["callDate"].get<std::string>()));

            for (Size i = 0; i < numberOfCallDates; i++)
            {
                Calendar nullCalendar = NullCalendar();

                Bond::Price myPrice(callPrice, Bond::Price::Clean);
                callSchedule.push_back(ext::make_shared<Callability>(myPrice, Callability::Call, callDate));
                callDate = nullCalendar.advance(callDate, 3, Months);
            }

            Date dated = Date(DateParser::parseISO(jData["request"]["callableBond"]["issueDate"].get<std::string>()));
            Date issue = dated;
            Date maturity = Date(DateParser::parseISO(jData["request"]["callableBond"]["maturityDate"].get<std::string>()));

            Natural settlementDays = jData["request"]["callableBond"]["settlementDays"].get<int>();
            Calendar bondCalendar = UnitedStates(UnitedStates::GovernmentBond);
            Real coupon = jData["request"]["callableBond"]["coupon"].get<float>();

            Frequency frequency = Quarterly;

            Real redemption = jData["request"]["callableBond"]["redemption"].get<float>();

            Real faceAmount = jData["request"]["callableBond"]["faceAmount"].get<float>();

            DayCounter bondDayCounter = ActualActual(ActualActual::Bond);

            // PFC1 shows no indication dates are being adjusted
            // for weekends/holidays for vanilla bonds
            BusinessDayConvention accrualConvention = Unadjusted;
            BusinessDayConvention paymentConvention = Unadjusted;

            Schedule sch(dated, maturity, Period(frequency), bondCalendar, accrualConvention,accrualConvention, DateGeneration::Backward, false);

            Size maxIterations = jData["request"]["maxIterations"];

            // Real accuracy = 1e-8;
            Real accuracy = jData["request"]["accuracy"];

            // Integer gridIntervals = 40;
            Integer gridIntervals = jData["request"]["gridIntervals"];

            // Real reversionParameter = .03;
            Real reversionParameter = jData["request"]["reversionParameter"].get<float>();

            // output price/yield results for varying volatility parameter

            Real sigma = QL_EPSILON;

            for (long unsigned int i = 0; i < jData["request"]["sigma"].size(); i++)
            {
                switch (i)
                {
                case 0:
                {
                    ext::shared_ptr<ShortRateModel> hw0(
                        new HullWhite(termStructure, reversionParameter, sigma));
                    ext::shared_ptr<PricingEngine> engine0(
                        new TreeCallableFixedRateBondEngine(hw0, gridIntervals));
                    CallableFixedRateBond callableBond(
                        settlementDays, faceAmount, sch, std::vector<Rate>(1, coupon),
                        bondDayCounter, paymentConvention, redemption, issue, callSchedule);
                    callableBond.setPricingEngine(engine0);
                    jData["response"][std::to_string(i)]["sigma"] =
                        0.0; // jData["request"]["sigma"][0];
                    jData["response"][std::to_string(i)]["cleanPrice"] = callableBond.cleanPrice();
                    jData["response"][std::to_string(i)]["yield"] =
                        100. * callableBond.yield(bondDayCounter, Compounded, frequency, accuracy,
                                                  maxIterations);
                    break;
                }
                case 1:
                {
                    sigma = jData["request"]["sigma"][i];
                    ext::shared_ptr<ShortRateModel> hw1(
                        new HullWhite(termStructure, reversionParameter, sigma));
                    ext::shared_ptr<PricingEngine> engine1(
                        new TreeCallableFixedRateBondEngine(hw1, gridIntervals));
                    CallableFixedRateBond callableBond(
                        settlementDays, faceAmount, sch, std::vector<Rate>(1, coupon),
                        bondDayCounter, paymentConvention, redemption, issue, callSchedule);
                    callableBond.setPricingEngine(engine1);
                    jData["response"][std::to_string(i)]["sigma"] =
                        0.01; // jData["request"]["sigma"][i];
                    jData["response"][std::to_string(i)]["cleanPrice"] = callableBond.cleanPrice();
                    jData["response"][std::to_string(i)]["yield"] =
                        100. * callableBond.yield(bondDayCounter, Compounded, frequency, accuracy,
                                                  maxIterations);
                    break;
                }
                case 2:
                {
                    sigma = jData["request"]["sigma"][i];
                    ext::shared_ptr<ShortRateModel> hw2(
                        new HullWhite(termStructure, reversionParameter, sigma));
                    ext::shared_ptr<PricingEngine> engine2(
                        new TreeCallableFixedRateBondEngine(hw2, gridIntervals));
                    CallableFixedRateBond callableBond(
                        settlementDays, faceAmount, sch, std::vector<Rate>(1, coupon),
                        bondDayCounter, paymentConvention, redemption, issue, callSchedule);
                    callableBond.setPricingEngine(engine2);
                    jData["response"][std::to_string(i)]["sigma"] =
                        0.03; // jData["request"]["sigma"][2];
                    jData["response"][std::to_string(i)]["cleanPrice"] = callableBond.cleanPrice();
                    jData["response"][std::to_string(i)]["yield"] =
                        100. * callableBond.yield(bondDayCounter, Compounded, frequency, accuracy,
                                                  maxIterations);
                    break;
                }
                case 3:
                {
                    sigma = jData["request"]["sigma"][i];
                    ext::shared_ptr<ShortRateModel> hw3(
                        new HullWhite(termStructure, reversionParameter, sigma));
                    ext::shared_ptr<PricingEngine> engine3(
                        new TreeCallableFixedRateBondEngine(hw3, gridIntervals));
                    CallableFixedRateBond callableBond(
                        settlementDays, faceAmount, sch, std::vector<Rate>(1, coupon),
                        bondDayCounter, paymentConvention, redemption, issue, callSchedule);
                    callableBond.setPricingEngine(engine3);
                    jData["response"][std::to_string(i)]["sigma"] =
                        0.06; // jData["request"]["sigma"][3];
                    jData["response"][std::to_string(i)]["cleanPrice"] = callableBond.cleanPrice();
                    jData["response"][std::to_string(i)]["yield"] =
                        100. * callableBond.yield(bondDayCounter, Compounded, frequency, accuracy,
                                                  maxIterations);
                    break;
                }
                case 4:
                {
                    sigma = jData["request"]["sigma"][i];
                    ext::shared_ptr<ShortRateModel> hw4(
                        new HullWhite(termStructure, reversionParameter, sigma));
                    ext::shared_ptr<PricingEngine> engine4(
                        new TreeCallableFixedRateBondEngine(hw4, gridIntervals));
                    CallableFixedRateBond callableBond(
                        settlementDays, faceAmount, sch, std::vector<Rate>(1, coupon),
                        bondDayCounter, paymentConvention, redemption, issue, callSchedule);
                    callableBond.setPricingEngine(engine4);
                    jData["response"][std::to_string(i)]["sigma"] =
                        0.012; // jData["request"]["sigma"][4];
                    jData["response"][std::to_string(i)]["cleanPrice"] = callableBond.cleanPrice();
                    jData["response"][std::to_string(i)]["yield"] =
                        100. * callableBond.yield(bondDayCounter, Compounded, frequency, accuracy,
                                                  maxIterations);
                    break;
                }
                default:
                    break;
                }
            }

            //std::cout << "JDATA" << std::setw(4) << jData["response"] << std::endl;
            std::string result = jData.dump();
            return result;
        }
        catch (std::exception &e)
        {
            std::cerr << e.what() << std::endl;
            return e.what();
        }
        catch (...)
        {
            std::cerr << "unknown error" << std::endl;
            return "unknown error";
        }
    };

    std::string calculateRegularBond(std::string data)
    {

        try
        {

            json incomingJsonData = json::parse(data);

            /*********************
             ***  MARKET DATA  ***
            *********************/

            Calendar calendar = TARGET();

            Date settlementDate = DateParser::parseISO(incomingJsonData["request"]["settlementDate"].get<std::string>());
            // must be a business day
            settlementDate = calendar.adjust(settlementDate);

            Integer fixingDays = incomingJsonData["request"]["fixingDays"];
            Natural settlementDays = incomingJsonData["request"]["settlementDays"];

            Date todaysDate = calendar.advance(settlementDate, -fixingDays, Days);
            // nothing to do with Date::todaysDate
            Settings::instance().evaluationDate() = todaysDate;

            Rate zc3mQuote = incomingJsonData["request"]["zeroCoupnRates"]["zc3mQuote"];
            Rate zc6mQuote = incomingJsonData["request"]["zeroCoupnRates"]["zc6mQuote"];
            Rate zc1yQuote = incomingJsonData["request"]["zeroCoupnRates"]["zc1yQuote"];

            ext::shared_ptr<Quote> zc3mRate(new SimpleQuote(zc3mQuote));
            ext::shared_ptr<Quote> zc6mRate(new SimpleQuote(zc6mQuote));
            ext::shared_ptr<Quote> zc1yRate(new SimpleQuote(zc1yQuote));

            DayCounter zcBondsDayCounter = Actual365Fixed();

            ext::shared_ptr<RateHelper> zc3m(
                new DepositRateHelper(Handle<Quote>(zc3mRate), 3 * Months, fixingDays, calendar,
                                      ModifiedFollowing, true, zcBondsDayCounter));
            ext::shared_ptr<RateHelper> zc6m(
                new DepositRateHelper(Handle<Quote>(zc6mRate), 6 * Months, fixingDays, calendar,
                                      ModifiedFollowing, true, zcBondsDayCounter));
            ext::shared_ptr<RateHelper> zc1y(
                new DepositRateHelper(Handle<Quote>(zc1yRate), 1 * Years, fixingDays, calendar,
                                      ModifiedFollowing, true, zcBondsDayCounter));

            // setup bonds
            Real redemption = 100.0;

            const Size numberOfBonds = 5;

            Date issueDates[] = {Date(DateParser::parseISO(
                                     incomingJsonData["request"]["issueDate"][0].get<std::string>())),
                                 Date(DateParser::parseISO(
                                     incomingJsonData["request"]["issueDate"][1].get<std::string>())),
                                 Date(DateParser::parseISO(
                                     incomingJsonData["request"]["issueDate"][2].get<std::string>())),
                                 Date(DateParser::parseISO(
                                     incomingJsonData["request"]["issueDate"][3].get<std::string>())),
                                 Date(DateParser::parseISO(
                                     incomingJsonData["request"]["issueDate"][4].get<std::string>()))};

            Date maturities[] = {Date(DateParser::parseISO(
                                     incomingJsonData["request"]["maturities"][0].get<std::string>())),
                                 Date(DateParser::parseISO(
                                     incomingJsonData["request"]["maturities"][1].get<std::string>())),
                                 Date(DateParser::parseISO(
                                     incomingJsonData["request"]["maturities"][2].get<std::string>())),
                                 Date(DateParser::parseISO(
                                     incomingJsonData["request"]["maturities"][3].get<std::string>())),
                                 Date(DateParser::parseISO(
                                     incomingJsonData["request"]["maturities"][4].get<std::string>()))};

            Real couponRates[] = {incomingJsonData["request"]["couponRates"][0],
                                  incomingJsonData["request"]["couponRates"][1],
                                  incomingJsonData["request"]["couponRates"][2],
                                  incomingJsonData["request"]["couponRates"][3],
                                  incomingJsonData["request"]["couponRates"][4]};

            Real marketQuotes[] = {incomingJsonData["request"]["marketQuotes"][0],
                                   incomingJsonData["request"]["marketQuotes"][1],
                                   incomingJsonData["request"]["marketQuotes"][2],
                                   incomingJsonData["request"]["marketQuotes"][3],
                                   incomingJsonData["request"]["marketQuotes"][4]};

            std::vector<ext::shared_ptr<SimpleQuote>> quote;
            for (double marketQuote : marketQuotes)
            {
                ext::shared_ptr<SimpleQuote> cp(new SimpleQuote(marketQuote));
                quote.push_back(cp);
            }

            RelinkableHandle<Quote> quoteHandle[numberOfBonds];
            for (Size i = 0; i < numberOfBonds; i++)
            {
                quoteHandle[i].linkTo(quote[i]);
            }

            // Definition of the rate helpers
            std::vector<ext::shared_ptr<BondHelper>> bondsHelpers;

            for (Size i = 0; i < numberOfBonds; i++)
            {

                Schedule schedule(issueDates[i], maturities[i], Period(Semiannual),
                                  UnitedStates(UnitedStates::GovernmentBond), Unadjusted, Unadjusted,
                                  DateGeneration::Backward, false);

                ext::shared_ptr<FixedRateBondHelper> bondHelper(new FixedRateBondHelper(
                    quoteHandle[i], settlementDays, 100.0, schedule,
                    std::vector<Rate>(1, couponRates[i]), ActualActual(ActualActual::Bond), Unadjusted,
                    redemption, issueDates[i]));

                // the above could also be done by creating a
                // FixedRateBond instance and writing:
                //
                // ext::shared_ptr<BondHelper> bondHelper(
                //         new BondHelper(quoteHandle[i], bond));
                //
                // This would also work for bonds that still don't have a
                // specialized helper, such as floating-rate bonds.

                bondsHelpers.push_back(bondHelper);
            }

            /*********************
            **  CURVE BUILDING **
            *********************/

            // Any DayCounter would be fine.
            // ActualActual::ISDA ensures that 30 years is 30.0
            DayCounter termStructureDayCounter = ActualActual(ActualActual::ISDA);

            // A depo-bond curve
            std::vector<ext::shared_ptr<RateHelper>> bondInstruments;

            // Adding the ZC bonds to the curve for the short end
            bondInstruments.push_back(zc3m);
            bondInstruments.push_back(zc6m);
            bondInstruments.push_back(zc1y);

            // Adding the Fixed rate bonds to the curve for the long end
            for (Size i = 0; i < numberOfBonds; i++)
            {
                bondInstruments.push_back(bondsHelpers[i]);
            }

            ext::shared_ptr<YieldTermStructure> bondDiscountingTermStructure(
                new PiecewiseYieldCurve<Discount, LogLinear>(settlementDate, bondInstruments,
                                                             termStructureDayCounter));

            // Building of the Libor forecasting curve
            // deposits
            Rate d1wQuote = incomingJsonData["request"]["liborRates"]["d1wQuote"];
            Rate d1mQuote = incomingJsonData["request"]["liborRates"]["d1mQuote"];
            Rate d3mQuote = incomingJsonData["request"]["liborRates"]["d3mQuote"];
            Rate d6mQuote = incomingJsonData["request"]["liborRates"]["d6mQuote"];
            Rate d9mQuote = incomingJsonData["request"]["liborRates"]["d9mQuote"];
            Rate d1yQuote = incomingJsonData["request"]["liborRates"]["d1yQuote"];
            // swaps
            Rate s2yQuote = incomingJsonData["request"]["swapRates"]["s2yQuote"];
            Rate s3yQuote = incomingJsonData["request"]["swapRates"]["s3yQuote"];
            Rate s5yQuote = incomingJsonData["request"]["swapRates"]["s5yQuote"];
            Rate s10yQuote = incomingJsonData["request"]["swapRates"]["s10yQuote"];
            Rate s15yQuote = incomingJsonData["request"]["swapRates"]["s15yQuote"];

            /********************
             ***    QUOTES    ***
            ********************/

            // SimpleQuote stores a value which can be manually changed;
            // other Quote subclasses could read the value from a database
            // or some kind of data feed.

            // deposits
            ext::shared_ptr<Quote> d1wRate(new SimpleQuote(d1wQuote));
            ext::shared_ptr<Quote> d1mRate(new SimpleQuote(d1mQuote));
            ext::shared_ptr<Quote> d3mRate(new SimpleQuote(d3mQuote));
            ext::shared_ptr<Quote> d6mRate(new SimpleQuote(d6mQuote));
            ext::shared_ptr<Quote> d9mRate(new SimpleQuote(d9mQuote));
            ext::shared_ptr<Quote> d1yRate(new SimpleQuote(d1yQuote));
            // swaps
            ext::shared_ptr<Quote> s2yRate(new SimpleQuote(s2yQuote));
            ext::shared_ptr<Quote> s3yRate(new SimpleQuote(s3yQuote));
            ext::shared_ptr<Quote> s5yRate(new SimpleQuote(s5yQuote));
            ext::shared_ptr<Quote> s10yRate(new SimpleQuote(s10yQuote));
            ext::shared_ptr<Quote> s15yRate(new SimpleQuote(s15yQuote));

            /*********************
             ***  RATE HELPERS ***
            *********************/

            // RateHelpers are built from the above quotes together with
            // other instrument dependant infos.  Quotes are passed in
            // relinkable handles which could be relinked to some other
            // data source later.

            // deposits
            DayCounter depositDayCounter = Actual360();

            ext::shared_ptr<RateHelper> d1w(
                new DepositRateHelper(Handle<Quote>(d1wRate), 1 * Weeks, fixingDays, calendar,
                                      ModifiedFollowing, true, depositDayCounter));
            ext::shared_ptr<RateHelper> d1m(
                new DepositRateHelper(Handle<Quote>(d1mRate), 1 * Months, fixingDays, calendar,
                                      ModifiedFollowing, true, depositDayCounter));
            ext::shared_ptr<RateHelper> d3m(
                new DepositRateHelper(Handle<Quote>(d3mRate), 3 * Months, fixingDays, calendar,
                                      ModifiedFollowing, true, depositDayCounter));
            ext::shared_ptr<RateHelper> d6m(
                new DepositRateHelper(Handle<Quote>(d6mRate), 6 * Months, fixingDays, calendar,
                                      ModifiedFollowing, true, depositDayCounter));
            ext::shared_ptr<RateHelper> d9m(
                new DepositRateHelper(Handle<Quote>(d9mRate), 9 * Months, fixingDays, calendar,
                                      ModifiedFollowing, true, depositDayCounter));
            ext::shared_ptr<RateHelper> d1y(
                new DepositRateHelper(Handle<Quote>(d1yRate), 1 * Years, fixingDays, calendar,
                                      ModifiedFollowing, true, depositDayCounter));

            // setup swaps
            Frequency swFixedLegFrequency = Annual;
            BusinessDayConvention swFixedLegConvention = Unadjusted;
            DayCounter swFixedLegDayCounter = Thirty360(Thirty360::European);
            ext::shared_ptr<IborIndex> swFloatingLegIndex(new Euribor6M);

            const Period forwardStart(1 * Days);

            ext::shared_ptr<RateHelper> s2y(new SwapRateHelper(
                Handle<Quote>(s2yRate), 2 * Years, calendar, swFixedLegFrequency, swFixedLegConvention,
                swFixedLegDayCounter, swFloatingLegIndex, Handle<Quote>(), forwardStart));
            ext::shared_ptr<RateHelper> s3y(new SwapRateHelper(
                Handle<Quote>(s3yRate), 3 * Years, calendar, swFixedLegFrequency, swFixedLegConvention,
                swFixedLegDayCounter, swFloatingLegIndex, Handle<Quote>(), forwardStart));
            ext::shared_ptr<RateHelper> s5y(new SwapRateHelper(
                Handle<Quote>(s5yRate), 5 * Years, calendar, swFixedLegFrequency, swFixedLegConvention,
                swFixedLegDayCounter, swFloatingLegIndex, Handle<Quote>(), forwardStart));
            ext::shared_ptr<RateHelper> s10y(
                new SwapRateHelper(Handle<Quote>(s10yRate), 10 * Years, calendar, swFixedLegFrequency,
                                   swFixedLegConvention, swFixedLegDayCounter, swFloatingLegIndex,
                                   Handle<Quote>(), forwardStart));
            ext::shared_ptr<RateHelper> s15y(
                new SwapRateHelper(Handle<Quote>(s15yRate), 15 * Years, calendar, swFixedLegFrequency,
                                   swFixedLegConvention, swFixedLegDayCounter, swFloatingLegIndex,
                                   Handle<Quote>(), forwardStart));

            /*********************
             **  CURVE BUILDING **
            *********************/

            // Any DayCounter would be fine.
            // ActualActual::ISDA ensures that 30 years is 30.0

            // A depo-swap curve
            std::vector<ext::shared_ptr<RateHelper>> depoSwapInstruments;
            depoSwapInstruments.push_back(d1w);
            depoSwapInstruments.push_back(d1m);
            depoSwapInstruments.push_back(d3m);
            depoSwapInstruments.push_back(d6m);
            depoSwapInstruments.push_back(d9m);
            depoSwapInstruments.push_back(d1y);
            depoSwapInstruments.push_back(s2y);
            depoSwapInstruments.push_back(s3y);
            depoSwapInstruments.push_back(s5y);
            depoSwapInstruments.push_back(s10y);
            depoSwapInstruments.push_back(s15y);
            ext::shared_ptr<YieldTermStructure> depoSwapTermStructure(
                new PiecewiseYieldCurve<Discount, LogLinear>(settlementDate, depoSwapInstruments,
                                                             termStructureDayCounter));

            // Term structures that will be used for pricing:
            // the one used for discounting cash flows
            RelinkableHandle<YieldTermStructure> discountingTermStructure;
            // the one used for forward rate forecasting
            RelinkableHandle<YieldTermStructure> forecastingTermStructure;

            /*********************
             * BONDS TO BE PRICED *
             **********************/
            // Date (DateParser::parseISO( incomingJsonData["maturities"][0].get<std::string>())),
            // Common data
            Real faceAmount = 100;

            // Pricing engine
            ext::shared_ptr<PricingEngine> bondEngine(
                new DiscountingBondEngine(discountingTermStructure));

            // Zero coupon bond

            ZeroCouponBond zeroCouponBond(
                settlementDays, UnitedStates(UnitedStates::GovernmentBond), faceAmount,
                Date(DateParser::parseISO(
                    incomingJsonData["request"]["bondsToEvaluate"]["zeroCouponBond"]["expiryDate"]
                        .get<std::string>())),
                Following,
                Real(incomingJsonData["request"]["bondsToEvaluate"]["zeroCouponBond"]["realPrice"]),
                Date(DateParser::parseISO(
                    incomingJsonData["request"]["bondsToEvaluate"]["zeroCouponBond"]["issueDate"]
                        .get<std::string>())));

            zeroCouponBond.setPricingEngine(bondEngine);

            // Fixed 4.5% US Treasury Note

            Schedule fixedBondSchedule(
                Date(DateParser::parseISO(
                    incomingJsonData["request"]["bondsToEvaluate"]["FixedRateBond"]["issueDate"]
                        .get<std::string>())),
                Date(DateParser::parseISO(
                    incomingJsonData["request"]["bondsToEvaluate"]["FixedRateBond"]["expiryDate"]
                        .get<std::string>())),
                Period(Semiannual), UnitedStates(UnitedStates::GovernmentBond), Unadjusted, Unadjusted,
                DateGeneration::Backward, false);

            FixedRateBond fixedRateBond(
                settlementDays, faceAmount, fixedBondSchedule, std::vector<Rate>(1, 0.045),
                ActualActual(ActualActual::Bond), ModifiedFollowing, 100.0,
                Date(DateParser::parseISO(
                    incomingJsonData["request"]["bondsToEvaluate"]["FixedRateBond"]["issueDate"]
                        .get<std::string>())));

            fixedRateBond.setPricingEngine(bondEngine);

            // Floating rate bond (3M USD Libor + 0.1%)
            // Should and will be priced on another curve later...

            // need to find out what is the deal with Libor here
            RelinkableHandle<YieldTermStructure> liborTermStructure;
            const ext::shared_ptr<IborIndex> libor3m(
                new USDLibor(Period(3, Months), liborTermStructure));
            libor3m->addFixing(Date(17, July, 2008), 0.0278625);

            // need to find out what is the deal with Libor here
            Schedule floatingBondSchedule(Date(21, October, 2005), Date(21, October, 2010),
                                          Period(Quarterly), UnitedStates(UnitedStates::NYSE),
                                          Unadjusted, Unadjusted, DateGeneration::Backward, true);

            FloatingRateBond floatingRateBond(
                settlementDays, faceAmount, floatingBondSchedule, libor3m, Actual360(),
                ModifiedFollowing, Natural(2),
                // Gearings
                std::vector<Real>(1, 1.0),
                // Spreads
                std::vector<Rate>(1, 0.001),
                // Caps
                std::vector<Rate>(),
                // Floors
                std::vector<Rate>(),
                // Fixing in arrears
                true,
                Real(incomingJsonData["request"]["bondsToEvaluate"]["FloatingRateBond"]["realPrice"]),
                Date(DateParser::parseISO(
                    incomingJsonData["request"]["bondsToEvaluate"]["FloatingRateBond"]["issueDate"]
                        .get<std::string>())));

            floatingRateBond.setPricingEngine(bondEngine);

            // Coupon pricers
            ext::shared_ptr<IborCouponPricer> pricer(new BlackIborCouponPricer);

            // optionLet volatilities
            Volatility volatility = 0.0;
            Handle<OptionletVolatilityStructure> vol;
            vol = Handle<OptionletVolatilityStructure>(
                ext::shared_ptr<OptionletVolatilityStructure>(new ConstantOptionletVolatility(
                    settlementDays, calendar, ModifiedFollowing, volatility, Actual365Fixed())));

            pricer->setCapletVolatility(vol);
            setCouponPricer(floatingRateBond.cashflows(), pricer);

            // Yield curve bootstrapping
            forecastingTermStructure.linkTo(depoSwapTermStructure);
            discountingTermStructure.linkTo(bondDiscountingTermStructure);

            // We are using the depo & swap curve to estimate the future Libor rates
            liborTermStructure.linkTo(depoSwapTermStructure);

            /***************
             * BOND PRICING *
             ****************/

            incomingJsonData["response"]["zeroCouponBond"]["NPV"] = zeroCouponBond.NPV();
            incomingJsonData["response"]["FixedRateBond"]["NPV"] = fixedRateBond.NPV();
            incomingJsonData["response"]["FloatingRateBond"]["NPV"] = floatingRateBond.NPV();

            incomingJsonData["response"]["zeroCouponBond"]["cleanPrice"] = zeroCouponBond.cleanPrice();
            incomingJsonData["response"]["FixedRateBond"]["cleanPrice"] = fixedRateBond.cleanPrice();
            incomingJsonData["response"]["FloatingRateBond"]["cleanPrice"] =
                floatingRateBond.cleanPrice();

            incomingJsonData["response"]["zeroCouponBond"]["dirtyPrice"] = zeroCouponBond.dirtyPrice();
            incomingJsonData["response"]["FixedRateBond"]["dirtyPrice"] = fixedRateBond.dirtyPrice();
            incomingJsonData["response"]["FloatingRateBond"]["dirtyPrice"] =
                floatingRateBond.dirtyPrice();

            incomingJsonData["response"]["FixedRateBond"]["accruedAmount"] =
                fixedRateBond.accruedAmount();
            incomingJsonData["response"]["FloatingRateBond"]["accruedAmount"] =
                floatingRateBond.accruedAmount();

            incomingJsonData["response"]["zeroCouponBond"]["previousCouponRate"] = "N/A";
            incomingJsonData["response"]["FixedRateBond"]["previousCouponRate"] =
                fixedRateBond.previousCouponRate();
            incomingJsonData["response"]["FloatingRateBond"]["previousCouponRate"] =
                floatingRateBond.previousCouponRate();

            incomingJsonData["response"]["zeroCouponBond"]["nextCouponRate"] = "N/A";
            incomingJsonData["response"]["FixedRateBond"]["nextCouponRate"] =
                fixedRateBond.nextCouponRate();
            incomingJsonData["response"]["FloatingRateBond"]["nextCouponRate"] =
                floatingRateBond.nextCouponRate();

            incomingJsonData["response"]["zeroCouponBond"]["Yield"] =
                zeroCouponBond.yield(Actual360(), Compounded, Annual);
            incomingJsonData["response"]["FixedRateBond"]["Yield"] =
                fixedRateBond.yield(Actual360(), Compounded, Annual);
            incomingJsonData["response"]["FloatingRateBond"]["Yield"] =
                floatingRateBond.yield(Actual360(), Compounded, Annual);

            incomingJsonData["response"]["FloatingRateBond"]["YieldtoCleanPrice"] =
                floatingRateBond.cleanPrice(floatingRateBond.yield(Actual360(), Compounded, Annual),
                                            Actual360(), Compounded, Annual, settlementDate);
            incomingJsonData["response"]["FloatingRateBond"]["CleanPriceToYield"] =
                floatingRateBond.yield(floatingRateBond.cleanPrice(), Actual360(), Compounded, Annual,
                                       settlementDate);
            /* "Yield to Price"
            "Price to Yield" */

            //std::cout << std::setw(4) << "Request: " << std::endl;
            //std::cout << std::setw(4) << incomingJsonData << std::endl;

            //std::cout << std::setw(4) << "Result: " << std::endl;
            //std::cout << std::setw(4) << incomingJsonData["response"] << std::endl;

            std::string result = incomingJsonData.dump();
            //std::cout << "result: " << result << std::endl;

            return result;
        }
        catch (std::exception &e)
        {
            std::cerr << e.what() << std::endl;
            return e.what();
        }
        catch (...)
        {
            std::cerr << "unknown error" << std::endl;
            return "unknown error";
        }
    }

    std::string calculateConvertibleBonds(std::string data)
    {
        try
        {

            json jData = json::parse(data);
            //std::cout << std::endl;

            Option::Type type(Option::Put);
            Real underlying = jData["request"]["underlying"];
            Real spreadRate = jData["request"]["spreadRate"];

            Spread dividendYield = jData["request"]["dividendYield"];
            Rate riskFreeRate = jData["request"]["riskFreeRate"];
            Volatility volatility = jData["request"]["volatility"];

            Integer settlementDays = jData["request"]["settlementDays"];
            Integer length = jData["request"]["length"];
            Real redemption = jData["request"]["redemption"];
            Real conversionRatio = redemption / underlying; // at the money

            // set up dates/schedules
            Calendar calendar = TARGET();
            Date today = calendar.adjust(Date::todaysDate());

            Settings::instance().evaluationDate() = today;
            Date settlementDate = calendar.advance(today, settlementDays, Days);
            Date exerciseDate = calendar.advance(settlementDate, length, Years);
            Date issueDate = calendar.advance(exerciseDate, -length, Years);

            BusinessDayConvention convention = ModifiedFollowing;

            Frequency frequency = Annual;

            Schedule schedule(issueDate, exerciseDate, Period(frequency), calendar, convention,
                              convention, DateGeneration::Backward, false);

            DividendSchedule dividends;
            CallabilitySchedule callability;

            std::vector<Real> coupons(1, 0.05);

            DayCounter bondDayCount = Thirty360(Thirty360::BondBasis);

            Integer callLength[] = {jData["request"]["calls"]["callLength"]["1"].get<int>(),
                                    jData["request"]["calls"]["callLength"]["2"].get<int>()};
            Integer putLength[] = {jData["request"]["puts"]["putLength"]["1"].get<int>()};

            Real callPrices[] = {jData["request"]["calls"]["callPrices"]["1"].get<double>(),
                                 jData["request"]["calls"]["callPrices"]["2"].get<double>()};
            Real putPrices[] = {jData["request"]["puts"]["putPrices"]["1"].get<double>()};

            // Load call schedules
            for (Size i = 0; i < LENGTH(callLength); i++)
            {
                callability.push_back(
                    ext::make_shared<SoftCallability>(Bond::Price(callPrices[i], Bond::Price::Clean),
                                                      schedule.date(callLength[i]), 1.20));
            }

            for (Size j = 0; j < LENGTH(putLength); j++)
            {
                callability.push_back(
                    ext::make_shared<Callability>(Bond::Price(putPrices[j], Bond::Price::Clean),
                                                  Callability::Put, schedule.date(putLength[j])));
            }

            // Assume dividends are paid every 6 months.
            for (Date d = today + 6 * Months; d < exerciseDate; d += 6 * Months)
            {
                dividends.push_back(ext::shared_ptr<Dividend>(new FixedDividend(1.0, d)));
            }

            DayCounter dayCounter = Actual365Fixed();
            Time maturity = dayCounter.yearFraction(settlementDate, exerciseDate);
            std::string method;

            ext::shared_ptr<Exercise> exercise(new EuropeanExercise(exerciseDate));
            ext::shared_ptr<Exercise> amExercise(new AmericanExercise(settlementDate, exerciseDate));

            Handle<Quote> underlyingH(ext::shared_ptr<Quote>(new SimpleQuote(underlying)));

            Handle<YieldTermStructure> flatTermStructure(ext::shared_ptr<YieldTermStructure>(
                new FlatForward(settlementDate, riskFreeRate, dayCounter)));

            Handle<YieldTermStructure> flatDividendTS(ext::shared_ptr<YieldTermStructure>(
                new FlatForward(settlementDate, dividendYield, dayCounter)));

            Handle<BlackVolTermStructure> flatVolTS(ext::shared_ptr<BlackVolTermStructure>(
                new BlackConstantVol(settlementDate, calendar, volatility, dayCounter)));

            ext::shared_ptr<BlackScholesMertonProcess> stochasticProcess(new BlackScholesMertonProcess(
                underlyingH, flatDividendTS, flatTermStructure, flatVolTS));

            Size timeSteps = jData["request"]["timeSteps"].get<int>();

            Handle<Quote> creditSpread(ext::shared_ptr<Quote>(new SimpleQuote(spreadRate)));

            ext::shared_ptr<Quote> rate(new SimpleQuote(riskFreeRate));

            Handle<YieldTermStructure> discountCurve(ext::shared_ptr<YieldTermStructure>(
                new FlatForward(today, Handle<Quote>(rate), dayCounter)));

            ext::shared_ptr<PricingEngine> engine(
                new BinomialConvertibleEngine<JarrowRudd>(stochasticProcess, timeSteps));

            ConvertibleFixedCouponBond europeanBond(exercise, conversionRatio, dividends, callability,
                                                    creditSpread, issueDate, settlementDays, coupons,
                                                    bondDayCount, schedule, redemption);
            europeanBond.setPricingEngine(engine);

            ConvertibleFixedCouponBond americanBond(amExercise, conversionRatio, dividends, callability,
                                                    creditSpread, issueDate, settlementDays, coupons,
                                                    bondDayCount, schedule, redemption);
            americanBond.setPricingEngine(engine);

            method = "Jarrow-Rudd";
            europeanBond.setPricingEngine(ext::shared_ptr<PricingEngine>(
                new BinomialConvertibleEngine<JarrowRudd>(stochasticProcess, timeSteps)));
            americanBond.setPricingEngine(ext::shared_ptr<PricingEngine>(
                new BinomialConvertibleEngine<JarrowRudd>(stochasticProcess, timeSteps)));

            jData["response"]["Tsiveriotis-Fernandes method"]["treeType"]["Jarrow-Rudd"]["American"]
                 ["NPV"] = americanBond.NPV();
            jData["response"]["Tsiveriotis-Fernandes method"]["treeType"]["Jarrow-Rudd"]["European"]
                 ["NPV"] = europeanBond.NPV();

            method = "Cox-Ross-Rubinstein";
            europeanBond.setPricingEngine(ext::shared_ptr<PricingEngine>(
                new BinomialConvertibleEngine<CoxRossRubinstein>(stochasticProcess, timeSteps)));
            americanBond.setPricingEngine(ext::shared_ptr<PricingEngine>(
                new BinomialConvertibleEngine<CoxRossRubinstein>(stochasticProcess, timeSteps)));
         
            jData["response"]["Tsiveriotis-Fernandes method"]["treeType"]["Cox-Ross-Rubinstein"]
                 ["American"]["NPV"] = americanBond.NPV();
            jData["response"]["Tsiveriotis-Fernandes method"]["treeType"]["Cox-Ross-Rubinstein"]
                 ["European"]["NPV"] = europeanBond.NPV();

            method = "Additive equiprobabilities";
            europeanBond.setPricingEngine(ext::shared_ptr<PricingEngine>(
                new BinomialConvertibleEngine<AdditiveEQPBinomialTree>(stochasticProcess, timeSteps)));
            americanBond.setPricingEngine(ext::shared_ptr<PricingEngine>(
                new BinomialConvertibleEngine<AdditiveEQPBinomialTree>(stochasticProcess, timeSteps)));

            jData["response"]["Tsiveriotis-Fernandes method"]["treeType"]["Additive equiprobabilities"]
                 ["American"]["NPV"] = americanBond.NPV();
            jData["response"]["Tsiveriotis-Fernandes method"]["treeType"]["Additive equiprobabilities"]
                 ["European"]["NPV"] = europeanBond.NPV();

            method = "Trigeorgis";
            europeanBond.setPricingEngine(ext::shared_ptr<PricingEngine>(
                new BinomialConvertibleEngine<Trigeorgis>(stochasticProcess, timeSteps)));
            americanBond.setPricingEngine(ext::shared_ptr<PricingEngine>(
                new BinomialConvertibleEngine<Trigeorgis>(stochasticProcess, timeSteps)));

            jData["response"]["Tsiveriotis-Fernandes method"]["treeType"]["Trigeorgis"]["American"]
                 ["NPV"] = americanBond.NPV();
            jData["response"]["Tsiveriotis-Fernandes method"]["treeType"]["Trigeorgis"]["European"]
                 ["NPV"] = europeanBond.NPV();

            method = "Tian";
            europeanBond.setPricingEngine(ext::shared_ptr<PricingEngine>(
                new BinomialConvertibleEngine<Tian>(stochasticProcess, timeSteps)));
            americanBond.setPricingEngine(ext::shared_ptr<PricingEngine>(
                new BinomialConvertibleEngine<Tian>(stochasticProcess, timeSteps)));

            jData["response"]["Tsiveriotis-Fernandes method"]["treeType"]["Tian"]["American"]["NPV"] =
                americanBond.NPV();
            jData["response"]["Tsiveriotis-Fernandes method"]["treeType"]["Tian"]["European"]["NPV"] =
                europeanBond.NPV();

            method = "Leisen-Reimer";
            europeanBond.setPricingEngine(ext::shared_ptr<PricingEngine>(
                new BinomialConvertibleEngine<LeisenReimer>(stochasticProcess, timeSteps)));
            americanBond.setPricingEngine(ext::shared_ptr<PricingEngine>(
                new BinomialConvertibleEngine<LeisenReimer>(stochasticProcess, timeSteps)));

            jData["response"]["Tsiveriotis-Fernandes method"]["treeType"]["Leisen-Reimer"]["American"]
                 ["NPV"] = americanBond.NPV();
            jData["response"]["Tsiveriotis-Fernandes method"]["treeType"]["Leisen-Reimer"]["European"]
                 ["NPV"] = europeanBond.NPV();

            method = "Joshi";
            europeanBond.setPricingEngine(ext::shared_ptr<PricingEngine>(
                new BinomialConvertibleEngine<Joshi4>(stochasticProcess, timeSteps)));
            americanBond.setPricingEngine(ext::shared_ptr<PricingEngine>(
                new BinomialConvertibleEngine<Joshi4>(stochasticProcess, timeSteps)));

            jData["response"]["Tsiveriotis-Fernandes method"]["treeType"]["Joshi"]["American"]["NPV"] =
                americanBond.NPV();
            jData["response"]["Tsiveriotis-Fernandes method"]["treeType"]["Joshi"]["European"]["NPV"] =
                europeanBond.NPV();

            std::string result = jData.dump();
            return result;
        }
        catch (std::exception &e)
        {
            std::cerr << e.what() << std::endl;
            return e.what();
        }
        catch (...)
        {
            std::cerr << "unknown error" << std::endl;
            return "unknown error";
        }
    };

    std::string calculateCVAIRS(std::string data)
    {
        try
        {

            json jData = json::parse(data);

            Calendar calendar = TARGET();
            Date todaysDate(DateParser::parseISO(jData["request"]["todaysDate"].get<std::string>()));
            // must be a business day
            todaysDate = calendar.adjust(todaysDate);

            Settings::instance().evaluationDate() = todaysDate;

            ext::shared_ptr<IborIndex> yieldIndx(new Euribor3M());
            Size tenorsSwapMkt[] = {5, 10, 15, 20, 25, 30};

            // rates ignoring counterparty risk:
            Rate ratesSwapmkt[] = {.03249, .04074, .04463, .04675, .04775, .04811};

            std::vector<ext::shared_ptr<RateHelper>> swapHelpers;
            for (Size i = 0; i < sizeof(tenorsSwapMkt) / sizeof(Size); i++)
                swapHelpers.push_back(ext::make_shared<SwapRateHelper>(
                    Handle<Quote>(ext::shared_ptr<Quote>(new SimpleQuote(ratesSwapmkt[i]))),
                    tenorsSwapMkt[i] * Years, TARGET(), Quarterly, ModifiedFollowing,
                    ActualActual(ActualActual::ISDA), yieldIndx));

            ext::shared_ptr<YieldTermStructure> swapTS(new PiecewiseYieldCurve<Discount, LogLinear>(
                2, TARGET(), swapHelpers, ActualActual(ActualActual::ISDA)));
            swapTS->enableExtrapolation();

            ext::shared_ptr<PricingEngine> riskFreeEngine(
                ext::make_shared<DiscountingSwapEngine>(Handle<YieldTermStructure>(swapTS)));

            std::vector<Handle<DefaultProbabilityTermStructure>> defaultIntensityTS;

            Size defaultTenors[] = {0, 12, 36, 60, 84, 120, 180, 240, 300, 360}; // months
            // Three risk levels:
            Real intensitiesLow[] = {0.0036, 0.0036, 0.0065, 0.0099, 0.0111, 0.0177,
                                     0.0177, 0.0177, 0.0177, 0.0177, 0.0177};
            Real intensitiesMedium[] = {0.0202, 0.0202, 0.0231, 0.0266, 0.0278, 0.0349,
                                        0.0349, 0.0349, 0.0349, 0.0349, 0.0349};
            Real intensitiesHigh[] = {0.0534, 0.0534, 0.0564, 0.06, 0.0614, 0.0696,
                                      0.0696, 0.0696, 0.0696, 0.0696, 0.0696};
            // Recovery rates:
            Real ctptyRRLow = 0.4, ctptyRRMedium = 0.35, ctptyRRHigh = 0.3;

            std::vector<Date> defaultTSDates;
            std::vector<Real> intesitiesVLow, intesitiesVMedium, intesitiesVHigh;

            for (Size i = 0; i < sizeof(defaultTenors) / sizeof(Size); i++)
            {
                defaultTSDates.push_back(
                    TARGET().advance(todaysDate, Period(defaultTenors[i], Months)));
                intesitiesVLow.push_back(intensitiesLow[i]);
                intesitiesVMedium.push_back(intensitiesMedium[i]);
                intesitiesVHigh.push_back(intensitiesHigh[i]);
            }

            defaultIntensityTS.emplace_back(ext::shared_ptr<DefaultProbabilityTermStructure>(
                new InterpolatedHazardRateCurve<BackwardFlat>(defaultTSDates, intesitiesVLow,
                                                              Actual360(), TARGET())));
            defaultIntensityTS.emplace_back(ext::shared_ptr<DefaultProbabilityTermStructure>(
                new InterpolatedHazardRateCurve<BackwardFlat>(defaultTSDates, intesitiesVMedium,
                                                              Actual360(), TARGET())));
            defaultIntensityTS.emplace_back(ext::shared_ptr<DefaultProbabilityTermStructure>(
                new InterpolatedHazardRateCurve<BackwardFlat>(defaultTSDates, intesitiesVHigh,
                                                              Actual360(), TARGET())));

            Volatility blackVol = 0.15;
            ext::shared_ptr<PricingEngine> ctptySwapCvaLow =
                ext::make_shared<CounterpartyAdjSwapEngine>(
                    Handle<YieldTermStructure>(swapTS), blackVol, defaultIntensityTS[0], ctptyRRLow);

            ext::shared_ptr<PricingEngine> ctptySwapCvaMedium =
                ext::make_shared<CounterpartyAdjSwapEngine>(
                    Handle<YieldTermStructure>(swapTS), blackVol, defaultIntensityTS[1], ctptyRRMedium);
            ext::shared_ptr<PricingEngine> ctptySwapCvaHigh =
                ext::make_shared<CounterpartyAdjSwapEngine>(
                    Handle<YieldTermStructure>(swapTS), blackVol, defaultIntensityTS[2], ctptyRRHigh);

            defaultIntensityTS[0]->enableExtrapolation();
            defaultIntensityTS[1]->enableExtrapolation();
            defaultIntensityTS[2]->enableExtrapolation();

            /// SWAP RISKY REPRICE----------------------------------------------

            // fixed leg
            Frequency fixedLegFrequency = Quarterly;
            BusinessDayConvention fixedLegConvention = ModifiedFollowing;
            DayCounter fixedLegDayCounter = ActualActual(ActualActual::ISDA);
            DayCounter floatingLegDayCounter = ActualActual(ActualActual::ISDA);

            QuantLib::VanillaSwap::Type swapType = QuantLib::VanillaSwap::Payer;
            ext::shared_ptr<IborIndex> yieldIndxS(new Euribor3M(Handle<YieldTermStructure>(swapTS)));
            std::vector<VanillaSwap> riskySwaps;
            for (Size i = 0; i < sizeof(tenorsSwapMkt) / sizeof(Size); i++)
                riskySwaps.push_back(
                    MakeVanillaSwap(tenorsSwapMkt[i] * Years, yieldIndxS, ratesSwapmkt[i], 0 * Days)
                        .withSettlementDays(2)
                        .withFixedLegDayCount(fixedLegDayCounter)
                        .withFixedLegTenor(Period(fixedLegFrequency))
                        .withFixedLegConvention(fixedLegConvention)
                        .withFixedLegTerminationDateConvention(fixedLegConvention)
                        .withFixedLegCalendar(calendar)
                        .withFloatingLegCalendar(calendar)
                        .withNominal(100.)
                        .withType(swapType));
         
            for (Size i = 0; i < riskySwaps.size(); i++)
            {
                riskySwaps[i].setPricingEngine(riskFreeEngine);
                // should recover the input here:
                Real nonRiskyFair = riskySwaps[i].fairRate();
                jData["response"]["tenorsSwapMkt"][i] = tenorsSwapMkt[i];
                // Low Risk:
                riskySwaps[i].setPricingEngine(ctptySwapCvaLow);
             
                jData["response"]["lowRisk"][i] = 10000. * (riskySwaps[i].fairRate() - nonRiskyFair);
                // Medium Risk:
                riskySwaps[i].setPricingEngine(ctptySwapCvaMedium);
             
                jData["response"]["MediumRisk"][i] = 10000. * (riskySwaps[i].fairRate() - nonRiskyFair);
                riskySwaps[i].setPricingEngine(ctptySwapCvaHigh);
             
                jData["response"]["HighRisk"][i] = 10000. * (riskySwaps[i].fairRate() - nonRiskyFair);
            }
            std::string result = jData.dump();
            return result;
        }

        catch (std::exception &e)
        {
            std::cerr << e.what() << std::endl;
            return e.what();
        }
        catch (...)
        {
            std::cerr << "unknown error" << std::endl;
            return "unknown error";
        }
    }

    std::string calculateBermudianOption(std::string data){
        try {
            json JsonData = json::parse(data);

            Calendar calendar = TARGET();

            Date todaysDate = Date(DateParser::parseISO(jData["request"]["todaysDate"].get<std::string>()));
            Date settlementDate = Date(DateParser::parseISO(jData["request"]["settlementDate"].get<std::string>()));
            Settings::instance().evaluationDate() = today;

            // our options
            (JsonData["request"]["optionType"] == "put")
                ?Option::Type type(Option::Put)
                :Option::Type type(Option::Call)

            Real underlying = JsonData["request"]["realUnderlying"];
            Real strike = JsonData["request"]["strikePrice"];
            Spread dividendYield = JsonData["request"]["dividendYield"];
            Rate riskFreeRate = JsonData["request"]["riskFreeRate"];
            Volatility volatility = JsonData["request"]["volatility"];
            Date maturity = Date(DateParser::parseISO(jData["request"]["MaturityDate"].get<std::string>()));
            DayCounter dayCounter = Actual365Fixed();

            std::vector<Date> exerciseDates;
            for (Integer i=1; i<=4; i++)
                exerciseDates.push_back(settlementDate + 3*i*Months);

            ext::shared_ptr<Exercise> bermudanExercise(
                new BermudanExercise(exerciseDates)
            );

            Handle<Quote> underlyingH(
                ext::shared_ptr<Quote>(
                    new SimpleQuote(underlying)
                )
            );

            // bootstrap the yield/dividend/vol curves
            Handle<YieldTermStructure> flatTermStructure(
                ext::shared_ptr<YieldTermStructure>(
                    new FlatForward(
                        settlementDate,
                        riskFreeRate, 
                        dayCounter
                    )
                )
            );

            Handle<YieldTermStructure> flatDividendTS(
                ext::shared_ptr<YieldTermStructure>(
                    new FlatForward(
                        settlementDate, 
                        dividendYield, 
                        dayCounter
                    )
                )
            );

            Handle<BlackVolTermStructure> flatVolTS(
                ext::shared_ptr<BlackVolTermStructure>(
                    new BlackConstantVol(
                        settlementDate, 
                        calendar, 
                        volatility,
                        dayCounter
                    )
                )
            );

            ext::shared_ptr<StrikedTypePayoff> payoff(
                new PlainVanillaPayoff(
                    type, 
                    strike
                )
            );

            ext::shared_ptr<BlackScholesMertonProcess> bsmProcess(
                new BlackScholesMertonProcess(
                    underlyingH, 
                    flatDividendTS,
                    flatTermStructure, 
                    flatVolTS
                )
            );
 
            VanillaOption bermudanOption(payoff, bermudanExercise);

             // Finite differences
            Size timeSteps = JsonData["request"]["FiniteDifferencesTimeSteps"];
            ext::shared_ptr<PricingEngine> fdengine =
                ext::make_shared<FdBlackScholesVanillaEngine>(
                    bsmProcess,
                    timeSteps,
                    timeSteps-1
                );
            bermudanOption.setPricingEngine(fdengine);

            JsonData["response"]["NPV"]["Finite-differences"] = europeanOption.NPV();
    
            // Binomial method: Jarrow-Rudd
            bermudanOption.setPricingEngine(
                ext::shared_ptr<PricingEngine>(
                    new BinomialVanillaEngine<JarrowRudd>(
                        bsmProcess,
                        timeSteps
                    )
                )
            );

            JsonData["response"]["NPV"]["Binomial-Jarrow-Rudd"] = europeanOption.NPV();


            //"Binomial Cox-Ross-Rubinstein";;
            bermudanOption.setPricingEngine(
                ext::shared_ptr<PricingEngine>(
                    new BinomialVanillaEngine<CoxRossRubinstein>(
                        bsmProcess,
                        timeSteps
                    
                    )
                )
            );

            JsonData["response"]["NPV"]["Binomial-Cox-Ross-Rubinstein"] = europeanOption.NPV();

            // Binomial method: Additive equiprobabilities
            bermudanOption.setPricingEngine(
                ext::shared_ptr<PricingEngine>(
                    new BinomialVanillaEngine<AdditiveEQPBinomialTree>(
                        bsmProcess,
                        timeSteps
                    )
                )
            );

            JsonData["response"]["NPV"]["Additive-equiprobabilities"] = europeanOption.NPV();

            // Binomial method: Binomial Trigeorgis
            bermudanOption.setPricingEngine(
                ext::shared_ptr<PricingEngine>(
                    new BinomialVanillaEngine<Trigeorgis>(
                        bsmProcess,
                        timeSteps
                    )
                )
            );

            JsonData["response"]["NPV"]["Binomial Trigeorgis"] = europeanOption.NPV();

            // Binomial method: Binomial Tian
            bermudanOption.setPricingEngine(
                ext::shared_ptr<PricingEngine>(
                    new BinomialVanillaEngine<Tian>(
                        bsmProcess,
                        timeSteps
                    )
                )
            );

            JsonData["response"]["NPV"]["Heston-semi-analytic"] = europeanOption.NPV();

            // Binomial method: Binomial Leisen-Reimer
            bermudanOption.setPricingEngine(
                ext::shared_ptr<PricingEngine>(
                    new BinomialVanillaEngine<LeisenReimer>(
                        bsmProcess,
                        timeSteps
                    )
                )
            );

            JsonData["response"]["NPV"]["Binomial Leisen-Reimer"] = europeanOption.NPV();

            // Binomial method: Binomial Joshi 
            bermudanOption.setPricingEngine(
                ext::shared_ptr<PricingEngine>(
                    new BinomialVanillaEngine<Joshi4>(
                        bsmProcess,
                        timeSteps
                    )
                )
            );

            JsonData["response"]["NPV"]["Binomial Joshi"] = europeanOption.NPV();

            return JsonData.dump()
        }
        catch (std::exception &e)
        {
            std::cerr << e.what() << std::endl;
            return e.what();
        }
        catch (...)
        {
            std::cerr << "unknown error" << std::endl;
            return "unknown error";
        }
    }

    std::string calcuateEuropeanOption(std::string data){
        try {

            json JsonData = json::parse(data);

            Calendar calendar = TARGET();

            Date todaysDate = Date(DateParser::parseISO(jData["request"]["todaysDate"].get<std::string>()));
            Date settlementDate = Date(DateParser::parseISO(jData["request"]["settlementDate"].get<std::string>()));
            Settings::instance().evaluationDate() = today;

            // our options
            (JsonData["request"]["optionType"] == "put")
                ?Option::Type type(Option::Put)
                :Option::Type type(Option::Call)

            Real underlying = JsonData["request"]["realUnderlying"];
            Real strike = JsonData["request"]["strikePrice"];
            Spread dividendYield = JsonData["request"]["dividendYield"];
            Rate riskFreeRate = JsonData["request"]["riskFreeRate"];
            Volatility volatility = JsonData["request"]["volatility"];
            Date maturity = Date(DateParser::parseISO(jData["request"]["MaturityDate"].get<std::string>()));
            DayCounter dayCounter = Actual365Fixed();

            std::vector<Date> exerciseDates;
            for (Integer i=1; i<=4; i++)
                exerciseDates.push_back(settlementDate + 3*i*Months);

            ext::shared_ptr<Exercise> europeanExercise(
                new EuropeanExercise(maturity));

            Handle<Quote> underlyingH(
                ext::shared_ptr<Quote>(
                    new SimpleQuote(
                        underlying
                    )
                )
            );

            // bootstrap the yield/dividend/vol curves
            Handle<YieldTermStructure> flatTermStructure(
                ext::shared_ptr<YieldTermStructure>(
                    new FlatForward(
                        settlementDate,
                        riskFreeRate, 
                        dayCounter
                    )
                )
            );

            Handle<YieldTermStructure> flatDividendTS(
                ext::shared_ptr<YieldTermStructure>(
                    new FlatForward(
                        settlementDate, 
                        dividendYield, 
                        dayCounter
                    )
                )
            );

            Handle<BlackVolTermStructure> flatVolTS(
                ext::shared_ptr<BlackVolTermStructure>(
                    new BlackConstantVol(
                        settlementDate, 
                        calendar, 
                        volatility,
                        dayCounter
                    )
                )
            );

            ext::shared_ptr<StrikedTypePayoff> payoff(
                new PlainVanillaPayoff(
                    type, 
                    strike
                )
            );

            ext::shared_ptr<BlackScholesMertonProcess> bsmProcess(
                new BlackScholesMertonProcess(
                    underlyingH, 
                    flatDividendTS,
                    flatTermStructure, 
                    flatVolTS
                )
            );

            VanillaOption europeanOption(payoff, europeanExercise);

            // Black-Scholes for European
            method = "Black-Scholes";
            europeanOption.setPricingEngine(
                ext::shared_ptr<PricingEngine>(
                    new AnalyticEuropeanEngine(bsmProcess)
                )
            );
            
            JsonData["response"]["NPV"]["Black-Scholes"] = europeanOption.NPV()
            
            //Vasicek rates model for European "Black Vasicek Model";
            Real r0 = riskFreeRate;
            Real a = JsonData["request"]["Black Vasicek Model"]["a"];
            Real b = JsonData["request"]["Black Vasicek Model"]["b"];;
            Real sigma_r = JsonData["request"]["Black Vasicek Model"]["sigma_r"];
            Real riskPremium = JsonData["request"]["Black Vasicek Model"]["riskPremium"];
            Real correlation = JsonData["request"]["Black Vasicek Model"]["correlation"];

            ext::shared_ptr<Vasicek> vasicekProcess(
                new Vasicek(r0, a, b, sigma_r, riskPremium)
            );

            europeanOption.setPricingEngine
                (ext::shared_ptr<PricingEngine>(
                    new AnalyticBlackVasicekEngine(
                        bsmProcess, 
                        vasicekProcess, 
                        correlation
                    )
                )
            );

            JsonData["response"]["NPV"]["Black-Vasicek-Model"] = europeanOption.NPV()

            // semi-analytic Heston for European "Heston semi-analytic";
            ext::shared_ptr<HestonProcess> hestonProcess(
                new HestonProcess(
                    flatTermStructure, 
                    flatDividendTS,
                    underlyingH, 
                    volatility*volatility,
                    1.0, 
                    volatility*volatility, 
                    0.001, 
                    0.0
                )
            );

            ext::shared_ptr<HestonModel> hestonModel(
                new HestonModel(hestonProcess)
            );

            europeanOption.setPricingEngine(
                ext::shared_ptr<PricingEngine>(
                    new AnalyticHestonEngine(hestonModel)
                    )
            );

            JsonData["response"]["NPV"]["Heston-semi-analytic"] = europeanOption.NPV();
    
            // semi-analytic Bates for European "Bates semi-analytic";
            ext::shared_ptr<BatesProcess> batesProcess(
                new BatesProcess(
                    flatTermStructure, 
                    flatDividendTS,
                    underlyingH, 
                    volatility*volatility, 
                    1.0, 
                    volatility*volatility, 
                    0.001, 
                    0.0,
                    1e-14, 
                    1e-14, 
                    1e-14
                )
            );

            ext::shared_ptr<BatesModel> batesModel(new BatesModel(batesProcess));

            europeanOption.setPricingEngine(
                ext::shared_ptr<PricingEngine>(
                    new BatesEngine(
                        batesModel
                    )
                )
            );
            
            JsonData["response"]["NPV"]["Bates-semi-analytic"] = europeanOption.NPV();

            // Integral (euro)
            europeanOption.setPricingEngine(
                ext::shared_ptr<PricingEngine>(
                    new IntegralEngine(
                        bsmProcess
                    )
                )
            );

            JsonData["response"]["NPV"]["Integral"] = europeanOption.NPV();

            // Finite differences
            Size timeSteps = JsonData["request"]["FiniteDifferencesTimeSteps"];
            ext::shared_ptr<PricingEngine> fdengine =
                ext::make_shared<FdBlackScholesVanillaEngine>(
                    bsmProcess,
                    timeSteps,
                    timeSteps-1
                );
            europeanOption.setPricingEngine(fdengine);

            JsonData["response"]["NPV"]["Finite-differences"] = europeanOption.NPV();
    
            // Binomial method: Jarrow-Rudd
            europeanOption.setPricingEngine(
                ext::shared_ptr<PricingEngine>(
                    new BinomialVanillaEngine<JarrowRudd>(
                        bsmProcess,
                        timeSteps
                    )
                )
            );

            JsonData["response"]["NPV"]["Binomial Jarrow-Rudd"] = europeanOption.NPV();

            europeanOption.setPricingEngine(
                ext::shared_ptr<PricingEngine>(
                    new BinomialVanillaEngine<CoxRossRubinstein>(
                        bsmProcess,
                        timeSteps
                    )
                )
            );

            JsonData["response"]["NPV"]["Binomial Cox-Ross-Rubinstein"] = europeanOption.NPV();
    
            // Binomial method: Additive equiprobabilities
            europeanOption.setPricingEngine(
                ext::shared_ptr<PricingEngine>(
                    new BinomialVanillaEngine<AdditiveEQPBinomialTree>(
                        bsmProcess,
                        timeSteps
                    )
                )
            );
            JsonData["response"]["NPV"]["Additive equiprobabilities"] = europeanOption.NPV();
            
            // Binomial method: Binomial Trigeorgis
            europeanOption.setPricingEngine(
                ext::shared_ptr<PricingEngine>(
                    new BinomialVanillaEngine<Trigeorgis>(
                        bsmProcess,
                        timeSteps
                    )
                )
            );

            JsonData["response"]["NPV"]["Binomial Trigeorgis"] = europeanOption.NPV();
            
            // Binomial method: Binomial Tian
            europeanOption.setPricingEngine(
                ext::shared_ptr<PricingEngine>(
                    new BinomialVanillaEngine<Tian>(
                        bsmProcess,
                        timeSteps
                    )
                )
            );

            JsonData["response"]["NPV"]["Binomial Tian"] = europeanOption.NPV();

            // Binomial method: Binomial Leisen-Reimer
            europeanOption.setPricingEngine(
                ext::shared_ptr<PricingEngine>(
                    new BinomialVanillaEngine<LeisenReimer>(
                        bsmProcess,
                        timeSteps
                    )
                )
            );

            JsonData["response"]["NPV"]["Binomial Leisen-Reimer"] = europeanOption.NPV();
            
            // Binomial method: Binomial Joshi
            method = "Binomial Joshi";
            europeanOption.setPricingEngine(
                ext::shared_ptr<PricingEngine>(
                    new BinomialVanillaEngine<Joshi4>(
                        bsmProcess,
                        timeSteps
                    )
                )
            );

            JsonData["response"]["NPV"]["Binomial Joshi"] = europeanOption.NPV();

            // Monte Carlo Method: MC (crude)
            timeSteps = JsonData["request"]["MonteCarloCrude"]["timeSteps"];
            method = "MC (crude)";
            Size mcSeed = JsonData["request"]["MonteCarloCrude"]["timeSteps"];
            ext::shared_ptr<PricingEngine> mcengine1;

            mcengine1 = MakeMCEuropeanEngine<PseudoRandom>(bsmProcess)
                .withSteps(timeSteps)
                .withAbsoluteTolerance(0.02)
                .withSeed(mcSeed);

            europeanOption.setPricingEngine(mcengine1);

            // Real errorEstimate = europeanOption.errorEstimate();

            JsonData["response"]["NPV"]["MonteCarlo(crude)"] = europeanOption.NPV();

            // Monte Carlo Method: QMC (Sobol)
            Size nSamples = JsonData["request"]["MonteCarlo-QMC(Sobol)"][nSamples];  // 2^15
    
            ext::shared_ptr<PricingEngine> mcengine2;

            mcengine2 = MakeMCEuropeanEngine<LowDiscrepancy>(bsmProcess)
                .withSteps(timeSteps)
                .withSamples(nSamples);

            europeanOption.setPricingEngine(mcengine2);

            JsonData["response"]["NPV"]["MonteCarlo-QMC(Sobol)"] = europeanOption.NPV();


            return JsonData.dump();
        } 
        catch (std::exception &e)
        {
            std::cerr << e.what() << std::endl;
            return e.what();
        }
        catch (...)
        {
            std::cerr << "unknown error" << std::endl;
            return "unknown error";
        }
    }

    std::string calcuateAmericanOption(std::string data){
        try {
            json JsonData = json::parse(data);

            Calendar calendar = TARGET();

            Date todaysDate = Date(DateParser::parseISO(jData["request"]["todaysDate"].get<std::string>()));
            Date settlementDate = Date(DateParser::parseISO(jData["request"]["settlementDate"].get<std::string>()));
            Settings::instance().evaluationDate() = today;

            // our options
            (JsonData["request"]["optionType"] == "put")
                ?Option::Type type(Option::Put)
                :Option::Type type(Option::Call)

            Real underlying = JsonData["request"]["realUnderlying"];
            Real strike = JsonData["request"]["strikePrice"];
            Spread dividendYield = JsonData["request"]["dividendYield"];
            Rate riskFreeRate = JsonData["request"]["riskFreeRate"];
            Volatility volatility = JsonData["request"]["volatility"];
            Date maturity = Date(DateParser::parseISO(jData["request"]["MaturityDate"].get<std::string>()));
            DayCounter dayCounter = Actual365Fixed();

            std::vector<Date> exerciseDates;
            for (Integer i=1; i<=4; i++)
                exerciseDates.push_back(settlementDate + 3*i*Months);

            ext::shared_ptr<Exercise> americanExercise(
                new AmericanExercise(
                    settlementDate,
                    maturity
                )
            );

            Handle<Quote> underlyingH(
                ext::shared_ptr<Quote>(
                    new SimpleQuote(underlying)
                )
            );

            // bootstrap the yield/dividend/vol curves
            Handle<YieldTermStructure> flatTermStructure(
                ext::shared_ptr<YieldTermStructure>(
                    new FlatForward(
                        settlementDate,
                        riskFreeRate,
                        dayCounter
                    )
                )
            );

            Handle<YieldTermStructure> flatDividendTS(
                ext::shared_ptr<YieldTermStructure>(
                    new FlatForward(
                        settlementDate,
                        dividendYield,
                        dayCounter
                    )
                )
            );

            Handle<BlackVolTermStructure> flatVolTS(
                ext::shared_ptr<BlackVolTermStructure>(
                    new BlackConstantVol(
                        settlementDate,
                        calendar,
                        volatility,
                        dayCounter
                    )
                )
            );

            ext::shared_ptr<StrikedTypePayoff> payoff(
                new PlainVanillaPayoff(type, strike)
            );

            ext::shared_ptr<BlackScholesMertonProcess> bsmProcess(
                new BlackScholesMertonProcess(
                    underlyingH,
                    flatDividendTS,
                    flatTermStructure,
                    flatVolTS
                )
            );

            VanillaOption americanOption(payoff, americanExercise);

            // Barone-Adesi and Whaley approximation for American
            americanOption.setPricingEngine(
                ext::shared_ptr<PricingEngine>(
                    new BaroneAdesiWhaleyApproximationEngine(bsmProcess)
                )
            );

            JsonData["response"]["NPV"]["Barone-Adesi/Whaley"] = americanOption.NPV()
    
            // Bjerksund and Stensland approximation for American
            americanOption.setPricingEngine(
                ext::shared_ptr<PricingEngine>(
                    new BjerksundStenslandApproximationEngine(bsmProcess)
                )
            );

            JsonData["response"]["NPV"]["Bjerksund/Stensland"] = americanOption.NPV()

            // Finite differences
            //Size timeSteps = 801;
            Size timeSteps = JsonData["request"]["FiniteDifferencesTimeSteps"]
            ext::shared_ptr<PricingEngine> fdengine =
                ext::make_shared<FdBlackScholesVanillaEngine>(
                    bsmProcess,
                    timeSteps,
                    timeSteps-1
                );

            americanOption.setPricingEngine(fdengine);
            JsonData["response"]["NPV"]["Finite-Differences"] = americanOption.NPV()

            // Binomial method: Jarrow-Rudd
            americanOption.setPricingEngine(
                ext::shared_ptr<PricingEngine>(
                    new BinomialVanillaEngine<JarrowRudd>(
                        bsmProcess,
                        timeSteps
                    )
                )
            );
            JsonData["response"]["NPV"]["Binomial-Jarrow-Rudd"] = americanOption.NPV()

            // "Binomial Cox-Ross-Rubinstein";
            americanOption.setPricingEngine(
                ext::shared_ptr<PricingEngine>(
                    new BinomialVanillaEngine<CoxRossRubinstein>(
                        bsmProcess,
                        timeSteps
                    )
                )
            );

            JsonData["response"]["NPV"]["Binomial-Cox-Ross-Rubinstein"] = americanOption.NPV()
            
            // Binomial method: Additive equiprobabilities
            americanOption.setPricingEngine(
                ext::shared_ptr<PricingEngine>(
                    new BinomialVanillaEngine<AdditiveEQPBinomialTree>(
                        bsmProcess,
                        timeSteps
                    )
                )
            );

            JsonData["response"]["NPV"]["Additive-equiprobabilities"] = americanOption.NPV()
            
            // Binomial method: Binomial Trigeorgis
            americanOption.setPricingEngine(
                ext::shared_ptr<PricingEngine>(
                    new BinomialVanillaEngine<Trigeorgis>(
                        bsmProcess,
                        timeSteps
                    )
                )
            );

            JsonData["response"]["NPV"]["Binomial-Trigeorgis"] = americanOption.NPV()

            // Binomial method: Binomial Tian
            americanOption.setPricingEngine(
                ext::shared_ptr<PricingEngine>(
                    new BinomialVanillaEngine<Tian>(
                        bsmProcess,
                        timeSteps
                    )
                )
            );

            JsonData["response"]["NPV"]["Binomial-Tian"] = americanOption.NPV()
            
            // Binomial-Leisen-Reimer
            americanOption.setPricingEngine(
                ext::shared_ptr<PricingEngine>(
                    new BinomialVanillaEngine<LeisenReimer>(
                        bsmProcess,
                        timeSteps
                    )
                )
            );

            JsonData["response"]["NPV"]["Binomial-Leisen-Reimer"] = americanOption.NPV()
            
            // Binomial method: Binomial Joshi
            americanOption.setPricingEngine(
                ext::shared_ptr<PricingEngine>(
                    new BinomialVanillaEngine<Joshi4>(
                        bsmProcess,timeSteps
                    )
                )
            );

            JsonData["response"]["NPV"]["Binomial-Joshi"] = americanOption.NPV()
            
            // Monte Carlo Method: MC (Longstaff Schwartz)
            ext::shared_ptr<PricingEngine> mcengine3;
            mcengine3 = MakeMCAmericanEngine<PseudoRandom>(bsmProcess)
                .withSteps(100)
                .withAntitheticVariate()
                .withCalibrationSamples(4096)
                .withAbsoluteTolerance(0.02)
                .withSeed(mcSeed);
            americanOption.setPricingEngine(mcengine3);
            JsonData["response"]["NPV"]["Monte-Carlo-Longstaff Schwartz"] = americanOption.NPV()

            return JsonData.dump();
        } 
        catch(std::exception &e)
        {
            std::cerr << e.what() << std::endl;
            return e.what();
        }
        catch (...)
        {
            std::cerr << "unknown error" << std::endl;
            return "unknown error";
        }
    }
  
    EMSCRIPTEN_BINDINGS(quantlib)
    {
        emscripten::function("calculateConvertibleBonds", &calculateConvertibleBonds);
        emscripten::function("calculateRegularBond", &calculateRegularBond);
        emscripten::function("calculateCallableBonds", &calculateCallableBonds);
        emscripten::function("calculateCVAIRS", &calculateCVAIRS);
        emscripten::function("calculateAmericanOptions", &calculateAmericanOptions);
        emscripten::function("calculateEuropeanOptions", &calculateEuropeanOptions);
        emscripten::function("calculateBermudianOptions", &calculateBermudianOptions);
    }

}
