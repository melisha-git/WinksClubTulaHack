"use client";
import { createContext, useState } from "react";
import ChatList from "@/components/chatList/chatList";
import Header from "@/components/header";

export const ThemeContext = createContext(null);

export default function Home() {
  const [section, setSection] = useState("event");
  return (
    <>
      <div className="">
        <ThemeContext.Provider value={[section, setSection]}>
          <Header />
          <ChatList nameList={"Мои мероприятия"} />
          <ChatList nameList={"Рекомендации"} />
        </ThemeContext.Provider>
      </div>
    </>
  );
}
