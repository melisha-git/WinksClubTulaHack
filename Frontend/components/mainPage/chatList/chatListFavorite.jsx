import { useQuery } from "react-query";
import { useSelector } from "react-redux";

import ChatItem from "./chatItem";
import MainPageSkeleton from "./skeleton/chatList";
import { getFavoriteProduct } from "@/service/mainPage/api";

export default function chatListFavorite() {
  const type = useSelector((state) => state.siteSelect.value);
  const { isSuccess, isLoading, isFetching, data } = useQuery(
    "chatFavItem",
    getFavoriteProduct
  );
  if (isLoading || isFetching) {
    return <MainPageSkeleton />;
  }
  if (isSuccess) {
    return (
      <>
        <div className="p-2 text-text-gray">Мои мероприятия</div>
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
