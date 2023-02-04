import { createAsyncThunk, createSlice, PayloadAction } from '@reduxjs/toolkit'
import { RootState, AppThunk } from '../../app/store'
import workerManager , { optionValuation  } from './workerManager'
import fetchOptionData from './pricerAPI';

export interface optionState {
  value: {
    ["immutables"]: {
        "ticker":string
        "excerciseStyle": 0 | 1 | 2,
        "id":string, 
        "settlementDate": string,
        "maturityDate": string,
        "optionType": 1 | -1,
        "strike": number,
    },
    "valuations":{
      [key: number]:optionValuation,
    }
  },
  status: 'idle' | 'loading' | 'failed',
}

const pricer = workerManager('worker.js')

const initialState: optionState = {
  value: {
    "immutables": {
        "ticker":"",
        "excerciseStyle": 0,
        "id":"", 
        "settlementDate": "",
        "maturityDate": "",
        "optionType": 1,
        "strike": 0,
    },

    "valuations":{},
  },
  status: 'idle'
}

export const addValuationAsync = createAsyncThunk(
  'pricer/addValuation',
  async (data: optionValuation) => {
    const response = await pricer.analyze(data);
    return response;
  }
);

export const initiatOptionAsync = createAsyncThunk(
  'pricer/initiatOptionAsync',
  async (data: optionState) => {
    const response = await fetchOptionData(data);
    return response;
  }
);

export const optionSlice = createSlice({
  name: 'option',
  initialState,
  reducers: {
    initiate_Option: (state, action: PayloadAction<optionState>) => {
      state.status = 'idle';
      state.value = action.payload.value;
    },
    add_valuation: (state, action: PayloadAction<optionValuation>) => {
      state.status = 'idle';
      state["value"]["valuations"][`${action.payload.request.id as number}`] = action.payload
    },
  },

  extraReducers: (builder) => {
    builder
      .addCase(addValuationAsync.pending, (state) => { state.status = 'loading' })
      .addCase(addValuationAsync.fulfilled, (state, action) => {
        state.status = 'idle';
        state["value"]["valuations"][`${action.payload.request.id as number}`] = action.payload
      })
      .addCase(addValuationAsync.rejected, (state) => { state.status = 'failed' })
      .addCase(initiatOptionAsync.pending, (state) => { state.status = 'loading' })
      .addCase(initiatOptionAsync.fulfilled, (state, action) => {
        state.status = 'idle';
        state["value"] = action.payload.value 
      })
      .addCase(initiatOptionAsync.rejected, (state) => { state.status = 'failed' })
  },
});

export const { initiate_Option , add_valuation} = optionSlice.actions;

export const selectOption = (state: RootState) => state.option.value;

export const addValuation = (data: optionValuation): AppThunk => (dispatch) => dispatch(addValuationAsync(data));

export const initiatOption = (data: optionState): AppThunk => (dispatch) => dispatch(initiatOptionAsync(data));
    
export default optionSlice.reducer;
