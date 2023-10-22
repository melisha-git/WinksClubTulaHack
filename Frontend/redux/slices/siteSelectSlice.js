import { createSlice } from "@reduxjs/toolkit";

const initialState = {
  value: "event",
};

export const siteSelectSlice = createSlice({
  name: "siteSelect",
  initialState,
  reducers: {
    eventSelect: (state) => {
      state.value = "event";
    },
    hobbySelect: (state) => {
      state.value = "hobby";
    },
  },
});

export const { eventSelect, hobbySelect } = siteSelectSlice.actions;

export default siteSelectSlice.reducer;
