// A mock function to mimic making an async request for data
import { optionState } from './pricerSlice'

export interface data  {
  "ticker":string,
  "todaysDate":string,
  "underlying": number,
  "dividendYield": number,
  "riskFreeRate": number,
  "optionPrice": number,
  "valuation"?:{},
}

export default function fetchOptionData(data:optionState) {
  return new Promise<optionState>((resolve) =>
    setTimeout(() => resolve({
      value: {
        "immutables": {
            "ticker":data.value.immutables.ticker,
            "excerciseStyle": data.value.immutables.excerciseStyle,
            "id":`opt-${performance.now()}`, 
            "settlementDate": data.value.immutables.settlementDate,
            "maturityDate": data.value.immutables.maturityDate,
            "optionType": data.value.immutables.optionType,
            "strike": data.value.immutables.strike,
        },
        "valuations":{}
      },
      status: 'idle'
    }), 500)
  );
}
