"use client";
import ChatListFavorite from "@/components/mainPage/chatList/chatListFavorite";
import ChatListRecondation from "@/components/mainPage/chatList/chatListRecondation";
import Header from "@/components/mainPage/header";
import AddBtnUI from "@/ui/button/addButton";

export default function Home() {
  return (
    <>
      <div className="">
        <Header />
        <ChatListFavorite />
        <ChatListRecondation />
        <AddBtnUI />
      </div>
    </>
  );
}
