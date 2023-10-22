import Link from "next/link";

import ImgRoundedUI from "@/ui/image/imageRounded/image";
import TagUI from "@/ui/tag/tag";

export default function ChatItem({ data, type }) {
  return (
    <Link href={`chat/${data.id}`}>
      <div className=" flex gap-2 px-2 items-center w-full h-20 bg-bg-white">
        <div className="">
          <ImgRoundedUI src={data?.image} alt={data?.name} size={56} />
        </div>
        <div className="flex-1">
          <div className="flex items-baseline gap-1 mb-2">
            <p className=" text-base font-semibold leading-none">
              {data?.name}
            </p>
          </div>
          <div className="flex gap-1">
            {data.tags.map((obj, id) => (
              <TagUI text={obj.name} key={id} />
            ))}
          </div>
        </div>
        {type === "event" ? (
          <div className=" w-16 text-right">{data.begin_time}</div>
        ) : (
          <div className=" bg-text-gray bg-opacity-50 text-bg-white py-1 px-2 rounded-full">
            53
          </div>
        )}
      </div>
    </Link>
  );
}
