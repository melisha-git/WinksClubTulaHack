import { createSlice } from "@reduxjs/toolkit";

const initialState = {
  value: "register",
};

export const loginElementSlice = createSlice({
  name: "loginElement",
  initialState,
  reducers: {
    login: (state) => {
      state.value = "login";
    },
    registeration: (state) => {
      state.value = "register";
    },
    codeVerify: (state) => {
      state.value = "codeVerify";
    },
  },
});

export const { login, registeration, codeVerify } = loginElementSlice.actions;

export default loginElementSlice.reducer;
