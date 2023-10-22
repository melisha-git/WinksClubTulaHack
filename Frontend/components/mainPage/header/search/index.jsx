import Image from "next/image";
import { useDispatch } from "react-redux";

import { close } from "@/redux/slices/searchElementSlice";

export default function Search() {
  const dispatch = useDispatch();
  return (
    <>
      <div className="flex items-center h-12 gap-2 px-2 bg-bg-white">
        <div>
          <Image
            src={"https://img.icons8.com/ios/50/back--v1.png"}
            height={25}
            width={25}
            onClick={() => dispatch(close())}
          />
        </div>
        <input
          type="text"
          placeholder="Поиск"
          id=""
          className="p-2 w-full  rounded-md border-2 border-bg-gray focus:outline-none"
        />
        <div>
          <Image
            src={"https://img.icons8.com/ios/50/filter--v1.png"}
            height={25}
            width={25}
          />
        </div>
      </div>
    </>
  );
}
