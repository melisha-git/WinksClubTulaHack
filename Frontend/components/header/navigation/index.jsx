import { useContext } from "react";
import { ThemeContext } from "@/app/page";

export default function Navigation() {
  const [section, setSection] = useContext(ThemeContext);
  return (
    <>
      <div className="flex items-center bg-bg-white">
        <div
          onClick={() => setSection("event")}
          className={`flex-1 text-center text-text-active py-3 font-medium ${
            section === "event" && "border-b-2 border-b-text-active"
          }`}
        >
          Мероприятия
        </div>
        <div
          onClick={() => setSection("hobby")}
          className={`flex-1 text-center text-text-active py-3 font-medium ${
            section === "hobby" && "border-b-2 border-b-text-active"
          }`}
        >
          Беседы по интересам
        </div>
      </div>
    </>
  );
}
