import Link from "next/link";

export default function AddBtnUI() {
  return (
    <div className="fixed bottom-2 right-2">
      <Link href={"/add-event"}>
        <div className=" bg-text-active h-16 w-16 rounded-full">
          <div className=" text-bg-white font-light text-5xl text-center h-full leading-[55px]">
            +
          </div>
        </div>
      </Link>
    </div>
  );
}
