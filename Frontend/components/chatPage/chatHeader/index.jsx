"use client";
import Image from "next/image";
import { useRouter } from "next/navigation";
import { useQuery } from "react-query";
import axios from "axios";

import ChatHeaderInfo from "./info";

async function getInfo(id) {
  const { data } = await axios.get(
    `http://94.103.86.64:8080/api/events?eventID=${id}`
  );
  return data;
}

export default function ChatHeader({ id }) {
  const router = useRouter();
  const { isSuccess, data } = useQuery({
    queryKey: ["infoItem", id],
    queryFn: () => getInfo(id),
  });
  if (isSuccess) {
    return (
      <>
        <div className="flex gap-3 item h-12 items-center fixed z-10 top-0 right-0 left-0  bg-bg-white p-2">
          <div className="" onClick={() => router.back()}>
            <Image
              src={"https://img.icons8.com/ios/50/back--v1.png"}
              height={25}
              width={25}
              className=" h-6 w-6"
            />
          </div>
          <ChatHeaderInfo data={data[0]} id={id} />
          <div className="text-xl font-bold px-2">
            <Image
              src={"https://img.icons8.com/ios-filled/25/ellipsis.png"}
              height={25}
              width={25}
              className=" h-6 w-6"
            />
          </div>
        </div>
      </>
    );
  }
}
