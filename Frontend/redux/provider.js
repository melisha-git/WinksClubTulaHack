"use client";
import React from "react";
import { store } from "@/redux/store.js";
import { Provider } from "react-redux";
import { QueryClient, QueryClientProvider } from "react-query";

const queryClient = new QueryClient();

function ReduxProvider({ children }) {
  return (
    <QueryClientProvider client={queryClient}>
      <Provider store={store}>{children}</Provider>
    </QueryClientProvider>
  );
}

export default ReduxProvider;
