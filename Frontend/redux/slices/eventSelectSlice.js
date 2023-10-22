import { createSlice } from "@reduxjs/toolkit";

const initialState = {
  value: 0,
};

export const eventSelectSlice = createSlice({
  name: "eventSelect",
  initialState,
  reducers: {
    eventSelect: (state) => {
      state.value = 1;
    },
    hobbySelect: (state) => {
      state.value = 2;
    },
    zeroSelect: (state) => {
      state.value = 0;
    },
  },
});

export const { eventSelect, hobbySelect, zeroSelec } = eventSelectSlice.actions;

export default eventSelectSlice.reducer;
