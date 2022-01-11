import { _RegularBonds_Type, _CVAIRS_Type, _ConvertibleBonds_Type, _CallableBonds_Type } from "./marketDataInterface"
export let CVAIRS:_CVAIRS_Type = {
    "request":{
        "name":"calculateCVAIRS",
        "id":"null",
        "todaysDate": "2004-03-10",
        "tenorsSwapMkt": {
            "1":5, 
            "2":10, 
            "3":15, 
            "4":20, 
            "5":25, 
            "6":30
        },
        "ratesSwapmkt":{
            "1": 0.03249, 
            "2": 0.04074, 
            "3": 0.04463, 
            "4": 0.04675, 
            "5": 0.04775, 
            "6": 0.04811
        },
        "defaultTenorsM":{
            "1":0, 
            "2":12, 
            "3":36, 
            "4":60, 
            "5":84, 
            "6":120, 
            "7":180, 
            "8":240, 
            "9":300, 
            "10":360
        },
        "intensities":{
            "low":[
                0.0036, 
                0.0036, 
                0.0065, 
                0.0099, 
                0.0111, 
                0.0177, 
                0.0177, 
                0.0177, 
                0.0177, 
                0.0177, 
                0.0177
            ],
            "medium":[
                0.0202, 
                0.0202, 
                0.0231, 
                0.0266, 
                0.0278, 
                0.0349, 
                0.0349, 
                0.0349, 
                0.0349, 
                0.0349,
                0.0349
            ],
            "high":[
                0.0534, 
                0.0534, 
                0.0564, 
                0.06, 
                0.0614, 
                0.0696,
                0.0696, 
                0.0696, 
                0.0696, 
                0.0696, 
                0.0696 
            ]          
        },
        "ctptyRR":{
                        "low":0.4,
                        "medium":0.35,
                        "high":0.3
        },
        "blackVol":0.15          
    },
    "response":{},
    "errors":{}
}

export let CallableBonds:_CallableBonds_Type = {
    "request":{
        "name":"calculateCallableBonds",
        "id":"null",
        "referenceDate": "2007-10-16",
        "HullWhiteReversionParameter":0.03,
        "bbCurveRate":0.055,
        "callPrice": 100,
        "numberOfCallDates":24,
        "callDate": "2006-09-15",
        "callableBond":{
            "issueDate": "2004-09-16",
            "maturityDate": "2012-09-15",
            "settlementDays":3,
            "coupon": 0.0465,
            "redemption": 100.0,
            "faceAmount": 100.0
        },
        "maxIterations": 1000,
        "accuracy": 1e-8,
        "gridIntervals": 40,
        "reversionParameter":0.03,
        "sigma": [
            0.00,
            0.01,
            0.03,
            0.06,
            0.12
        ]
    },
    "response":{

    },

    "errors":{
            
    }
}

export let ConvertibleBonds:_ConvertibleBonds_Type = {
    "request":{
        "name":"calculateConvertibleBonds",
        "id":"null",
        "underlying": 36.0,
        "spreadRate": 0.005,
        "dividendYield": 0.02,
        "riskFreeRate": 0.06,
        "volatility": 0.20,
        "settlementDays": 3,
        "length": 5,
        "redemption": 100.0,
        "calls":{
            "callPrices": {
                "1":101.5,
                "2":100.85
            },
            "callLength": {
                "1": 2,
                "2": 4
            }
        },
        "puts":{
            "putPrices": {
                "1":105.0
            },
            "putLength": {
                "1": 3
            }
        },
        "timeSteps":801
            
    },
    "response":{

    },

    "errors":{
            
    }
}

export let RegularBonds:_RegularBonds_Type = {
    "request":{
        "id":"null",
        "name":"calculateRegularBond",
        "bondsToEvaluate":{
            "zeroCouponBond":{
                "issueDate":"2003-08-15",
                "expiryDate":"2013-08-15",
                "realPrice": 116.92
            },
            "FixedRateBond":{
                "issueDate":"2005-10-21",
                "expiryDate":"2010-10-21",
                "Period":"semiannual",
                "BusinessDayConvention":"Unadjusted"
            },
            "FloatingRateBond":{
                "issueDate":"2007-05-15",
                "expiryDate":"2017-05-15",
                "Period":"Quarterly",
                "BusinessDayConvention":"Unadjusted",
                "realPrice":100.00
            }
        },
        "settlementDate": "2008-09-18",
        "fixingDays":3,
        "settlementDays":3,
        "zeroCoupnRates":{
            "zc3mQuote": 0.0096,
            "zc6mQuote": 0.0145,
            "zc1yQuote": 0.0194
        },
        "liborRates":{
            "d1wQuote":0.043375,
            "d1mQuote":0.031875,
            "d3mQuote":0.0320375,
            "d6mQuote":0.03385,
            "d9mQuote":0.0338125,
            "d1yQuote":0.0335125
        },
        "swapRates":{
            "s2yQuote":0.0295,
            "s3yQuote":0.0323,
            "s5yQuote":0.0359,
            "s10yQuote":0.0412,
            "s15yQuote":0.0433
        },
        "redemption": 100,
        "numberOfBonds":5,
        "issueDate":[
            "2005-05-15",
            "2005-06-15",
            "2006-06-30",
            "2002-11-15",
            "1987-05-15"   
        ],
        "maturities":[
            "2010-08-31",
            "2011-08-31",
            "2013-08-31",
            "2018-08-15",
            "2038-05-15"
        ],
        "couponRates": [
            0.02375,
            0.04625,
            0.03125,
            0.04000,
            0.04500
        ],
        "marketQuotes":[
            100.390625,
            106.21875,
            100.59375,
            101.6875,
            102.140625
        ]
    },

    "response":{

    },

    "errors":{
            
    }
}