import { configureStore, ThunkAction, Action } from '@reduxjs/toolkit';
import optionReducer from '../features/pricer/pricerSlice'

export const store = configureStore({
  reducer: {
    option: optionReducer,
  },
});

export type AppDispatch = typeof store.dispatch;
export type RootState = ReturnType<typeof store.getState>;
export type AppThunk<ReturnType = void> = ThunkAction<
  ReturnType,
  RootState,
  unknown,
  Action<string>
>;
