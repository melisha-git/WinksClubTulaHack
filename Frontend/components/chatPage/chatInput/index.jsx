"use client";

import { useForm } from "react-hook-form";
import { useMutation } from "react-query";
import axios from "axios";

async function createProduct(data) {
  return axios.post("http://94.103.86.64:8080/api/sendmessage", data);
}

export default function ChatInput({ id }) {
  const { register, handleSubmit, reset } = useForm();
  const { error, mutate } = useMutation((newProduct) =>
    createProduct(newProduct)
  );
  const onSubmit = (data) => {
    const employee = {
      userID: parseInt(localStorage.getItem("userId")),
      eventID: parseInt(id),
      // time: Date.now(),
      ...data,
    };
    // alert(JSON.stringify(employee));
    mutate(JSON.stringify(employee));
    reset();
  };
  return (
    <>
      <div className=" w-full h-10 fixed bottom-0 left-0 right-0">
        <form
          onSubmit={handleSubmit(onSubmit)}
          className="flex px-1 bg-bg-white"
          action=""
        >
          <input
            type="text"
            name=""
            id=""
            {...register("message")}
            className=" grow w-full h-10 no-scroll border-0 focus:outline-none  px-2"
          />
          <button type="submit" value="submit" className="mr-2">
            <svg
              width="24"
              height="24"
              viewBox="0 0 24 24"
              fill="none"
              xmlns="http://www.w3.org/2000/svg"
            >
              <path
                d="M18.6357 15.6701L20.3521 10.5208C21.8516 6.02242 22.6013 3.77322 21.414 2.58595C20.2268 1.39869 17.9776 2.14842 13.4792 3.64788L8.32987 5.36432C4.69923 6.57453 2.88392 7.17964 2.36806 8.06698C1.87731 8.91112 1.87731 9.95369 2.36806 10.7978C2.88392 11.6852 4.69923 12.2903 8.32987 13.5005C8.91282 13.6948 9.2043 13.792 9.44793 13.9551C9.68404 14.1131 9.88687 14.316 10.0449 14.5521C10.208 14.7957 10.3052 15.0872 10.4995 15.6701C11.7097 19.3008 12.3148 21.1161 13.2022 21.6319C14.0463 22.1227 15.0889 22.1227 15.933 21.6319C16.8204 21.1161 17.4255 19.3008 18.6357 15.6701Z"
                stroke="#1C274C"
                stroke-width="1.5"
              />
              <path
                d="M17.7894 6.21064L13.5789 10.3748"
                stroke="#1C274C"
                stroke-width="1.5"
                stroke-linecap="round"
              />
            </svg>
          </button>
        </form>
      </div>
    </>
  );
}
