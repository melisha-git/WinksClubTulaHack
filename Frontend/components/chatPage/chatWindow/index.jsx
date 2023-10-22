"use client";

import React, { useRef, useEffect } from "react";
import { useQuery } from "react-query";
import axios from "axios";

import MessageUI from "@/ui/message/message";

async function getMessage(id) {
  const { data } = await axios.get(`http://94.103.86.64:8080/chat/${id}`);
  return data;
}

export default function ChatWindow({ number, id }) {
  const { isSuccess, isLoading, data } = useQuery({
    queryKey: ["chatMessage", id],
    queryFn: () => getMessage(id),
    refetchInterval: 500,
  });
  const ref = useRef(null);
  useEffect(() => {
    if (isLoading) {
      ref.current.scrollIntoView({
        behavior: "smooth",
        block: "end",
      });
    }
  }, [isLoading]);
  return (
    <div className="absolute bottom-10 top-12 left-0 right-0 pt-4">
      <div className="flex h-full flex-col-reverse overflow-y-auto no-scroll">
        <div ref={ref} />
        {isSuccess &&
          data.map((item, id) => {
            return (
              <MessageUI
                key={id}
                number={id}
                name="Alex"
                userId={item.user_id}
                user={item.login}
                message={item.message}
              />
            );
          })}
      </div>
    </div>
  );
}
