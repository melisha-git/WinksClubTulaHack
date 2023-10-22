import Link from "next/link";
import { useForm } from "react-hook-form";
import axios from "axios";
import { useMutation } from "react-query";
import { useRouter } from "next/navigation";
import Image from "next/image";
import { useDispatch } from "react-redux";

import { registeration } from "@/redux/slices/loginElementSlice";

async function createProduct(data) {
  return axios.post("http://94.103.86.64:8080/register", data);
}

export default function CodeVerify() {
  const dispatch = useDispatch();
  const router = useRouter();
  const { register, handleSubmit, reset } = useForm();

  const { error, mutate } = useMutation({
    mutationFn: (newProduct) => createProduct(newProduct),
    onSuccess: (data) => {
      // alert(data);
      localStorage.removeItem("userId");
      localStorage.removeItem("login");
      localStorage.removeItem("password");
      localStorage.setItem("userId", data.data.id);
      router.push("/");
    },
  });

  const onSubmit = (data) => {
    const employee = {
      login: localStorage.getItem("login"),
      password: localStorage.getItem("password"),
      ...data,
    };
    mutate(JSON.stringify(employee));
    reset();
  };
  return (
    <>
      <div className="flex items-center mx-2  mb-4">
        <Image
          src={"https://img.icons8.com/ios/50/back--v1.png"}
          height={25}
          width={25}
          onClick={() => dispatch(registeration())}
        />
        <div className=" ml-20 text-2xl text-text-active font-bold">
          Подтверждение
        </div>
      </div>

      <div className="mx-2 ">
        <button className="border-2 border-text-active rounded-lg text-base font-semibold text-text-active h-14 w-full mb-2">
          <Link href="https://t.me/WinksRegisterBot" target="_blank">
            Подтвердите через Telegram бота
          </Link>
        </button>
      </div>
      <form onSubmit={handleSubmit(onSubmit)} className="mx-2">
        {/* <div className=" font-medium mb-1 text-center">и напишите код</div> */}
        <input
          type="text"
          placeholder="Напишите код"
          {...register("code")}
          id=""
          className="p-2 w-full h-14 rounded-md border-2 border-bg-gray focus:outline-none mb-2"
        />

        <button
          type="submit"
          value="submit"
          className=" bg-text-active rounded-lg text-base text-bg-white h-14 w-full mb-2"
        >
          Вход
        </button>
      </form>
      {error && (
        <div className=" mx-2 p-2 text-text-error font-medium rounded-md border-2 border-text-error">
          Неверный логин или код
        </div>
      )}
    </>
  );
}
