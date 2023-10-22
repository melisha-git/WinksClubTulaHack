"use client";
import Image from "next/image";
import { useParams, useRouter } from "next/navigation";
import { useQuery } from "react-query";
import axios from "axios";

import InfoElement from "@/components/infoPage";

async function getInfo(id) {
  const { data } = await axios.get(
    `http://94.103.86.64:8080/api/events?eventID=${id}`
  );
  return data;
}

export default function ChatPage() {
  const params = useParams();
  const router = useRouter();
  const id = params.id;
  const { isSuccess, data } = useQuery({
    queryKey: ["infoItem", id],
    queryFn: () => getInfo(id),
  });

  if (isSuccess) {
    return (
      <>
        <div className="flex gap-3 justify-between h-12  bg-bg-white p-2">
          <div className="" onClick={() => router.back()}>
            <Image
              src={"https://img.icons8.com/ios/50/back--v1.png"}
              height={25}
              width={25}
              className=" h-6 w-6"
            />
          </div>
        </div>
        <InfoElement data={data[0]} />;
      </>
    );
  }
}
