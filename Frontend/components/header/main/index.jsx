import Image from "next/image";

export default function MainSection() {
  return (
    <>
      <div className="flex items-center h-12 px-2 bg-bg-white">
        <div>
          <Image
            src={"https://img.icons8.com/ios-glyphs/30/menu--v1.png"}
            height={25}
            width={25}
          />
        </div>
        <div className="flex-1 text-center text-text-active text-base font-semibold">
          MeetMe
        </div>
        <div>
          <Image
            src={"https://img.icons8.com/ios-glyphs/30/search--v1.png"}
            height={25}
            width={25}
          />
        </div>
      </div>
    </>
  );
}
