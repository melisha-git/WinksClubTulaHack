import { createSlice } from "@reduxjs/toolkit";

const initialState = {
  value: false,
};

export const searchElementSlice = createSlice({
  name: "searchElement",
  initialState,
  reducers: {
    open: (state) => {
      state.value = true;
    },
    close: (state) => {
      state.value = false;
    },
  },
});

export const { open, close } = searchElementSlice.actions;

export default searchElementSlice.reducer;
