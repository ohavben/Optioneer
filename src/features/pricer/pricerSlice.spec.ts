import pricerReducer, { addValuationAsync, } from './pricerSlice';

interface optionState {
  value: {
    "immutables": {
        "excerciseStyle": 0 | 1 | 2,
        "id":string, 
        "settlementDate": string,
        "maturityDate": string,
        "optionType": 1 | -1,
        "strike": number,
    },
    "valuations":{
      [key: number]:{
        "todaysDate":string,
        "underlying": number,
        "dividendYield": number,
        "riskFreeRate": number,
        "optionPrice": number,
        "valuation"?:{},
      }
    }
  },
  status: 'idle' | 'loading' | 'failed';
}

describe('pricer reducer', () => {
  const initialState: optionState = {
    value: {
      "immutables": {
          "excerciseStyle": 0,
          "id":`opt-${1}`, 
          "settlementDate": "",
          "maturityDate": "",
          "optionType": 1 ,
          "strike": 0,
          
      },
      "valuations":{
        [`${2}`]:{
          "todaysDate":"",
          "underlying": 0,
          "dividendYield": 0,
          "riskFreeRate": 0,
          "optionPrice": 0
        }
      }
    },
    status: 'idle',
  };
  it('should handle initial state', () => {
    expect(pricerReducer(undefined, { type: 'unknown' })).toEqual({
      value: {
        "immutables": {
          "excerciseStyle": 0,
          "id":`opt-${1}`, 
          "settlementDate": "",
          "maturityDate": "",
          "optionType": 1 ,
          "strike": 0,
          "valuations":{
            [`${2}`]:{
              "todaysDate":"",
              "underlying": 0,
              "dividendYield": 0,
              "riskFreeRate": 0,
              "optionPrice": 0
            }
          }
        }
      },
      status: 'idle',
    });
  });
/*
  it('should handle addValuationAsync', () => {
    const actual = pricerReducer(initialState, addValuationAsync({
      "request": {
          "excerciseStyle": 2,
          "id":performance.now(),
          "todaysDate":"1998-05-15",
          "settlementDate": "1998-05-17",
          "maturityDate": "1999-05-17",
          "optionType":1,
          "underlying": 36,
          "strike": 40,
          "dividendYield": 0,
          "riskFreeRate": 0.06,
          "optionPrice": 2.20
      },
      "response":{},
      "errors":{}
  }));
    expect(actual.value).toEqual(4);
  });

  it('should handle decrement', () => {
    const actual = counterReducer(initialState, decrement());
    expect(actual.value).toEqual(2);
  });

  it('should handle incrementByAmount', () => {
    const actual = counterReducer(initialState, incrementByAmount(2));
    expect(actual.value).toEqual(5);
  });*/

});
