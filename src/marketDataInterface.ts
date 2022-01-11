export type _CVAIRS_Type  = {
    "request":{
        "name":string,
        "id":string,
        "todaysDate": string,
        "tenorsSwapMkt": {
            "1":number, 
            "2":number, 
            "3":number, 
            "4":number, 
            "5":number, 
            "6":number
        },
        "ratesSwapmkt":{
            "1": number, 
            "2": number, 
            "3": number, 
            "4": number, 
            "5": number, 
            "6": number
        },
        "defaultTenorsM":{
            "1":number, 
            "2":number, 
            "3":number, 
            "4":number, 
            "5":number, 
            "6":number, 
            "7":number, 
            "8":number, 
            "9":number, 
            "10":number
        },
        "intensities":{
            "low":number[],
            "medium":number[],
            "high":number[]          
        },
        "ctptyRR":{
                        "low":number,
                        "medium":number,
                        "high":number
        },
        "blackVol":number          
    },
    "response":{},
    "errors":{}
}

export type _CallableBonds_Type = {
    "request":{
        "name":string,
        "id":string,
        "referenceDate": string,
        "HullWhiteReversionParameter":number,
        "bbCurveRate":number,
        "callPrice": number,
        "numberOfCallDates":number,
        "callDate": string,
        "callableBond":{
            "issueDate": string,
            "maturityDate": string,
            "settlementDays":number,
            "coupon": number,
            "redemption": number,
            "faceAmount": number
        },
        "maxIterations": number,
        "accuracy": number,
        "gridIntervals": number,
        "reversionParameter":number,
        "sigma": number[]
    },
    "response":{},

    "errors":{}
}

export type _ConvertibleBonds_Type = {
    "request":{
        "name":string,
        "id":string,
        "underlying": number,
        "spreadRate": number,
        "dividendYield": number,
        "riskFreeRate": number,
        "volatility": number,
        "settlementDays": number,
        "length": number,
        "redemption": number,
        "calls":{
            "callPrices": {
                "1":number,
                "2":number
            },
            "callLength": {
                "1": number,
                "2": number
            }
        },
        "puts":{
            "putPrices": {
                "1":number
            },
            "putLength": {
                "1":number
            }
        },
        "timeSteps":number
            
    },
    "response":{},

    "errors":{}
}

export type _RegularBonds_Type = {
    "request":{
        "id":string,
        "name":string,
        "bondsToEvaluate":{
            "zeroCouponBond":{
                "issueDate":string,
                "expiryDate":string,
                "realPrice": number
            },
            "FixedRateBond":{
                "issueDate":string,
                "expiryDate":string,
                "Period":string,
                "BusinessDayConvention":string
            },
            "FloatingRateBond":{
                "issueDate":string,
                "expiryDate":string,
                "Period":string,
                "BusinessDayConvention":string,
                "realPrice":number
            }
        },
        "settlementDate": string,
        "fixingDays":number,
        "settlementDays":number,
        "zeroCoupnRates":{
            "zc3mQuote": number,
            "zc6mQuote": number,
            "zc1yQuote": number
        },
        "liborRates":{
            "d1wQuote":number,
            "d1mQuote":number,
            "d3mQuote":number,
            "d6mQuote":number,
            "d9mQuote":number,
            "d1yQuote":number
        },
        "swapRates":{
            "s2yQuote":number,
            "s3yQuote":number,
            "s5yQuote":number,
            "s10yQuote":number,
            "s15yQuote":number
        },
        "redemption": number,
        "numberOfBonds":number,
        "issueDate":string[],
        "maturities":string[],
        "couponRates": number[],
        "marketQuotes":number[]
    },

    "response":{

    },

    "errors":{
            
    }
}

export interface _CVAIRS_Interface {
    "request":{
        "name":string,
        "id":string,
        "todaysDate": string,
        "tenorsSwapMkt": {
            "1":number, 
            "2":number, 
            "3":number, 
            "4":number, 
            "5":number, 
            "6":number
        },
        "ratesSwapmkt":{
            "1": number, 
            "2": number, 
            "3": number, 
            "4": number, 
            "5": number, 
            "6": number
        },
        "defaultTenorsM":{
            "1":number, 
            "2":number, 
            "3":number, 
            "4":number, 
            "5":number, 
            "6":number, 
            "7":number, 
            "8":number, 
            "9":number, 
            "10":number
        },
        "intensities":{
            "low":number[],
            "medium":number[],
            "high":number[]          
        },
        "ctptyRR":{
                        "low":number,
                        "medium":number,
                        "high":number
        },
        "blackVol":number          
    },
    "response":{},
    "errors":{}
}

export interface _CallableBonds_Interface  {
    "request":{
        "name":string,
        "id":string | null,
        "referenceDate": string,
        "HullWhiteReversionParameter":number,
        "bbCurveRate":number,
        "callPrice": number,
        "numberOfCallDates":number,
        "callDate": string,
        "callableBond":{
            "issueDate": string,
            "maturityDate": string,
            "settlementDays":number,
            "coupon": number,
            "redemption": number,
            "faceAmount": number
        },
        "maxIterations": number,
        "accuracy": number,
        "gridIntervals": number,
        "reversionParameter":number,
        "sigma": number[]
    },
    "response":{},

    "errors":{}
}

export interface _ConvertibleBonds_Interface  {
    "request":{
        "name":string,
        "id":string,
        "underlying": number,
        "spreadRate": number,
        "dividendYield": number,
        "riskFreeRate": number,
        "volatility": number,
        "settlementDays": number,
        "length": number,
        "redemption": number,
        "calls":{
            "callPrices": {
                "1":number,
                "2":number
            },
            "callLength": {
                "1": number,
                "2": number
            }
        },
        "puts":{
            "putPrices": {
                "1":number
            },
            "putLength": {
                "1":number
            }
        },
        "timeSteps":number
            
    },
    "response":{},

    "errors":{}
}

export interface _RegularBonds_Interface {
    "request":{
        "id":string,
        "name":string,
        "bondsToEvaluate":{
            "zeroCouponBond":{
                "issueDate":string,
                "expiryDate":string,
                "realPrice": number
            },
            "FixedRateBond":{
                "issueDate":string,
                "expiryDate":string,
                "Period":string,
                "BusinessDayConvention":string
            },
            "FloatingRateBond":{
                "issueDate":string,
                "expiryDate":string,
                "Period":string,
                "BusinessDayConvention":string,
                "realPrice":number
            }
        },
        "settlementDate": string,
        "fixingDays":number,
        "settlementDays":number,
        "zeroCoupnRates":{
            "zc3mQuote": number,
            "zc6mQuote": number,
            "zc1yQuote": number
        },
        "liborRates":{
            "d1wQuote":number,
            "d1mQuote":number,
            "d3mQuote":number,
            "d6mQuote":number,
            "d9mQuote":number,
            "d1yQuote":number
        },
        "swapRates":{
            "s2yQuote":number,
            "s3yQuote":number,
            "s5yQuote":number,
            "s10yQuote":number,
            "s15yQuote":number
        },
        "redemption": number,
        "numberOfBonds":number,
        "issueDate":string[],
        "maturities":string[],
        "couponRates": number[],
        "marketQuotes":number[]
    },

    "response":{

    },

    "errors":{
            
    }
}


/*export type CVAIRS_type  {
    "request":{
        "name":string,
        "id":null | number,
        "todaysDate": string,
        "tenorsSwapMkt": {
            "1":number, 
            "2":number, 
            "3":number, 
            "4":number, 
            "5":number, 
            "6":number
        },
        "ratesSwapmkt":{
            "1": number, 
            "2": number, 
            "3": number, 
            "4": number, 
            "5": number, 
            "6": number
        },
        "defaultTenorsM":{
            "1":number, 
            "2":number, 
            "3":number, 
            "4":number, 
            "5":number, 
            "6":number, 
            "7":number, 
            "8":number, 
            "9":number, 
            "10":number
        },
        "intensities":{
            "low":number[],
            "medium":number[],
            "high":number[]          
        },
        "ctptyRR":{
                        "low":number,
                        "medium":number,
                        "high":number
        },
        "blackVol":number          
    },
    "response":{},
    "errors":{}
}

export type CallableBonds_type  {
    "request":{
        "name":string,
        "id":null | number,
        "referenceDate": string,
        "HullWhiteReversionParameter":number,
        "bbCurveRate":number,
        "callPrice": number,
        "numberOfCallDates":number,
        "callDate": string,
        "callableBond":{
            "issueDate": string,
            "maturityDate": string,
            "settlementDays":number,
            "coupon": number,
            "redemption": number,
            "faceAmount": number
        },
        "maxIterations": number,
        "accuracy": number,
        "gridIntervals": number,
        "reversionParameter":number,
        "sigma": number[]
    },
    "response":{},

    "errors":{}
}

export type ConvertibleBonds_type  {
    "request":{
        "name":string,
        "id":null | number,
        "underlying": number,
        "spreadRate": number,
        "dividendYield": number,
        "riskFreeRate": number,
        "volatility": number,
        "settlementDays": number,
        "length": number,
        "redemption": number,
        "calls":{
            "callPrices": {
                "1":number,
                "2":number
            },
            "callLength": {
                "1": number,
                "2": number
            }
        },
        "puts":{
            "putPrices": {
                "1":number
            },
            "putLength": {
                "1":number
            }
        },
        "timeSteps":number
            
    },
    "response":{},

    "errors":{}
}

export type RegularBonds_type {
    "request":{
        "id":null | number,
        "name":string,
        "bondsToEvaluate":{
            "zeroCouponBond":{
                "issueDate":string,
                "expiryDate":string,
                "realPrice": number
            },
            "FixedRateBond":{
                "issueDate":string,
                "expiryDate":string,
                "Period":string,
                "BusinessDayConvention":string
            },
            "FloatingRateBond":{
                "issueDate":string,
                "expiryDate":string,
                "Period":string,
                "BusinessDayConvention":string,
                "realPrice":number
            }
        },
        "settlementDate": string,
        "fixingDays":number,
        "settlementDays":number,
        "zeroCoupnRates":{
            "zc3mQuote": number,
            "zc6mQuote": number,
            "zc1yQuote": number
        },
        "liborRates":{
            "d1wQuote":number,
            "d1mQuote":number,
            "d3mQuote":number,
            "d6mQuote":number,
            "d9mQuote":number,
            "d1yQuote":number
        },
        "swapRates":{
            "s2yQuote":number,
            "s3yQuote":number,
            "s5yQuote":number,
            "s10yQuote":number,
            "s15yQuote":number
        },
        "redemption": number,
        "numberOfBonds":number,
        "issueDate":string[],
        "maturities":string[],
        "couponRates": number[],
        "marketQuotes":number[]
    },

    "response":{

    },

    "errors":{
            
    }
}*/