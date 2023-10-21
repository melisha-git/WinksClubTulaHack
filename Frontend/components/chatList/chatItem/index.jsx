import ImgRoundedUI from "@/ui/image/imageRounded/image";
import TagUI from "@/ui/tag/tag";
import Link from "next/link";

export default function ChatItem({ data, type }) {
  return (
    <Link href={"/1"}>
      <div className=" flex gap-2 px-2 items-center w-full h-20 bg-bg-white">
        <div className="">
          <ImgRoundedUI src={data?.image} alt={data?.name} />
        </div>
        <div className="flex-1">
          <div className="flex items-baseline gap-1 mb-2">
            <p className=" text-base font-semibold leading-none">
              {data?.name}
            </p>
            {/* <p className=" ">
              {data?.subscribers}
              {data.max_subscribers && `/${data.max_subscribers}`} уч.
            </p> */}
          </div>
          <div className="flex gap-1">
            <TagUI text="Хакатон" />
            <TagUI text="Онлайн" />
            <TagUI text="Образование" />
            <TagUI text="IT" />
          </div>
        </div>
        {type === "event" ? (
          <div className=" w-16 text-right">{data.time}</div>
        ) : (
          <div className=" bg-text-gray bg-opacity-50 text-bg-white py-1 px-2 rounded-full">
            53
          </div>
        )}
      </div>
    </Link>
  );
}
