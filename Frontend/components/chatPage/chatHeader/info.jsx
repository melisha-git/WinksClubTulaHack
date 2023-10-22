import Link from "next/link";
import Image from "next/image";

export default function ChatHeaderInfo({ id, data }) {
  return (
    <>
      <div className="flex-1">
        <Link href={`/info/${id}`}>
          <div className="flex gap-2">
            <Image
              src={data.image}
              height={40}
              width={40}
              className=" w-10 h-10 rounded-full"
              alt="Yoga"
            />
            <div>
              <div className=" text-base font-semibold leading-4">
                {data.name}
              </div>
              <div className=" text-xs text-text-gray">Описание</div>
            </div>
          </div>
        </Link>
      </div>
    </>
  );
}
