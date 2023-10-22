"use client";
import { useParams } from "next/navigation";

import ChatWindow from "@/components/chatPage/chatWindow";
import ChatInput from "@/components/chatPage/chatInput";
import ChatHeader from "@/components/chatPage/chatHeader";

export default function ChatPage() {
  const params = useParams();
  return (
    <>
      <ChatHeader id={params.id} />
      <ChatWindow id={params.id} />
      <ChatInput id={params.id} />
    </>
  );
}
