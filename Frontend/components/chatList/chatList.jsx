import { ChatItemData } from "@/data";
import ChatItem from "./chatItem";
import { useContext } from "react";
import { ThemeContext } from "@/app/page";

export default function ChatList({ nameList }) {
  const [section, setSection] = useContext(ThemeContext);
  return (
    <>
      <div className="p-2 text-text-gray">{nameList}</div>
      {ChatItemData.map((item, id) =>
        item.type === section ? (
          <ChatItem data={item} type={section} key={id} />
        ) : (
          ""
        )
      )}
    </>
  );
}
