import { useQuery } from "react-query";
import { useSelector } from "react-redux";

import MainPageSkeleton from "./skeleton/chatList";
import ChatItem from "./chatItem";
import { getProduct } from "@/service/mainPage/api";

export default function ChatListRecondation() {
  const type = useSelector((state) => state.siteSelect.value);
  const { isSuccess, isFetching, isLoading, data } = useQuery(
    "chatRecItem",
    getProduct
  );
  if (isLoading || isFetching) {
    return <MainPageSkeleton />;
  }
  if (isSuccess) {
    return (
      <>
        <div className="p-2 text-text-gray">Рекомендации</div>
        {data.map((item, id) =>
          item.type === type ? (
            <ChatItem data={item} type={type} key={id} />
          ) : (
            ""
          )
        )}
      </>
    );
  }
}
