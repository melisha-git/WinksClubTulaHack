export default function MessageUI({ name, message, user, userId }) {
  const value = localStorage.getItem("userId") == userId;
  if (value) {
    return (
      <div className="m-1 text-right">
        <div className="mb-2 text-text-active">You</div>
        <div className=" bg-text-active text-bg-white self-start float-right w-3/4 p-2  rounded-lg text-white">
          {message}
          <div className="mt-2 text-[10px]">15:56</div>
        </div>
      </div>
    );
  } else {
    return (
      <div className="m-1">
        <div className="mb-1 text-text-active">{user}</div>
        <div className=" bg-text-gray text-bg-white self-start w-3/4 p-2 rounded-lg text-white">
          {message}
          <div className="mt-2 text-[10px]">15:56</div>
        </div>
      </div>
    );
  }
}
