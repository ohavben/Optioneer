import React, { useState } from 'react';

import { useAppSelector, useAppDispatch } from '../../app/hooks';
import { addValuationAsync, selectOption } from './pricerSlice';
import styles from './Pricer.module.css';

export function Pricer() {
  const option = useAppSelector(selectOption);
  const dispatch = useAppDispatch();
/*  
onClick={() => dispatch(addValuationAsync({
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
        }))}
*/
  return (
    <div>
      <div className={styles.row}>
        <button
          className={styles.button}
          onClick={() => dispatch(addValuationAsync({
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
        })).then(d => console.log(d.payload))}
        >
          Create Portfolio
        </button>
        <button
          className={styles.asyncButton}
          onClick={() => dispatch(addValuationAsync({
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
        })).then(d => console.log(d))}
        >
          Add Option
        </button>
        <button
          className={styles.button}
          onClick={() => dispatch(addValuationAsync({
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
        })).then(d => console.log(d))}
        >
          Evaluate Option
        </button>
      </div>
    </div>
  );
}
