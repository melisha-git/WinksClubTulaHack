import Image from "next/image";

import TagUI from "@/ui/tag/tag";
import ChatList from "@/components/mainPage/chatList/chatListFavorite";
import Navigation from "@/components/mainPage/header/navigation";

export default function InfoElement({ data }) {
  return (
    <>
      <div className=" bg-bg-white p-2">
        <div className="flex gap-2 mb-2">
          <Image
            src={data.image}
            height={50}
            width={50}
            className=" w-12 h-12 rounded-full"
            alt={data.name}
          />
          <div>
            <div className=" text-base font-semibold">{data.name}</div>
            <div className=" text-xs text-text-gray">
              {data.subscribers} участников
            </div>
          </div>
        </div>
        <div className=" text-base mb-2">{data.description}</div>
        <div className="flex gap-1">
          <TagUI text="Хакатон" />
          <TagUI text="Онлайн" />
          <TagUI text="Образование" />
          <TagUI text="IT" />
        </div>
      </div>
      <Navigation />
      <ChatList nameList={""} />
    </>
  );
}
