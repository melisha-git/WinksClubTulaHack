"use client";
import MessageUI from "@/ui/message/message";
import { useRouter } from "next/navigation";
import React, { useRef, useEffect, useState } from "react";

export default function ChatPage() {
  const router = useRouter();
  const [number, setNumber] = useState(5);
  const ref = useRef(null);

  useEffect(() => {
    if (number) {
      ref.current.scrollIntoView({
        behavior: "smooth",
        block: "end",
      });
    }
  }, [number]);

  return (
    <>
      <div className="flex gap-3 item items-center sticky z-10 top-0 right-0 left-0 h-16 bg-bg-white p-2">
        <div
          className=" text-xl font-bold px-2"
          onClick={() => router.back()}
        >{`<`}</div>
        <div className="flex-1">CHAT APP</div>
        <div
          onClick={() => setNumber(number + 1)}
          className="text-xl font-bold px-2"
        >
          :
        </div>
      </div>
      <div className="flex flex-col-reverse pb-12">
        <div ref={ref} />
        {[...Array(number)].map((_, id) => {
          return <MessageUI key={id} number={id} />;
        })}
      </div>

      <div>
        <input
          type="text"
          name=""
          id=""
          className="w-full h-10 px-2 fixed z-10 bottom-0 right-0 left-0"
        />
      </div>
    </>
  );
}
