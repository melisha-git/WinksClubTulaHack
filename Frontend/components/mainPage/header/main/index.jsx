import Image from "next/image";
import { useDispatch } from "react-redux";
import Link from "next/link";

import { open } from "@/redux/slices/searchElementSlice";

export default function MainSection() {
  const dispatch = useDispatch();

  return (
    <>
      <div className="flex items-center h-12 px-2 bg-bg-white">
        <div>
          <Link href={"/login"}>
            <Image
              src={"https://img.icons8.com/ios-glyphs/30/login-rounded.png"}
              height={25}
              width={25}
              alt="Login"
            />
          </Link>
        </div>
        <div className="flex-1 text-center text-text-active text-base font-semibold">
          MeetMe
        </div>
        <div>
          <Image
            src={"https://img.icons8.com/ios-glyphs/30/search--v1.png"}
            height={25}
            width={25}
            alt="Search"
            onClick={() => dispatch(open())}
            className="cursor-pointer"
          />
        </div>
      </div>
    </>
  );
}
