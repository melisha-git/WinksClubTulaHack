"use client";
import Image from "next/image";
import { useRouter } from "next/navigation";
import { useSelector } from "react-redux";

import AddEvents from "@/components/eventPage/event/addEvents";
import ChoiceEvents from "@/components/eventPage/event/choiceEvents";

export default function AddEvent() {
  const item = useSelector((state) => state.eventSelect.value);
  const router = useRouter();

  return (
    <>
      <div className="flex gap-2 px-4 py-3 bg-bg-white mb-2">
        <Image
          src={"https://img.icons8.com/ios/50/back--v1.png"}
          height={25}
          width={25}
          className=" h-6 w-6"
          onClick={() => router.back()}
        />
        <div className=" text-base font-semibold text-text-active">
          Создать новый чат
        </div>
      </div>
      {item === 0 && <ChoiceEvents />}
      {item === 1 && <AddEvents type="мероприятия" />}
      {item === 2 && <AddEvents type="беседы" />}
    </>
  );
}
