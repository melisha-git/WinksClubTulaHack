import { configureStore } from "@reduxjs/toolkit";
import searchElement from "./slices/searchElementSlice.js";
import loginElement from "./slices/loginElementSlice.js";
import eventSelect from "./slices/eventSelectSlice.js";
import siteSelect from "./slices/siteSelectSlice.js";

export const store = configureStore({
  reducer: {
    searchElement,
    loginElement,
    eventSelect,
    siteSelect,
  },
});
