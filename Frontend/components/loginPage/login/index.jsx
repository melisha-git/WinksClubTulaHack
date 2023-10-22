import { useDispatch } from "react-redux";
import { useForm } from "react-hook-form";
import { useMutation } from "react-query";
import axios from "axios";
import { useRouter } from "next/navigation";

import { registeration } from "@/redux/slices/loginElementSlice";

async function createProduct(data) {
  return axios.post("http://94.103.86.64:8080/login", data);
}

export default function LoginComp() {
  const router = useRouter();
  const { register, handleSubmit, reset } = useForm();
  const dispatch = useDispatch();

  const { error, mutate } = useMutation({
    mutationFn: (newProduct) => createProduct(newProduct),
    onSuccess: (data) => {
      // alert(JSON.stringify(data.data.id));
      localStorage.removeItem("userId");
      localStorage.setItem("userId", data.data.id);
      router.push("/");
    },
  });

  const onSubmit = (data) => {
    mutate(JSON.stringify(data));
    reset();
  };
  return (
    <>
      <div className="text-center text-2xl text-text-active font-bold">
        Вход
      </div>
      <form onSubmit={handleSubmit(onSubmit)} className="mx-2">
        <div className=" font-medium mb-1">Никнейм</div>
        <input
          type="text"
          placeholder="Введите никнейм Телеграм"
          {...register("login")}
          id=""
          className="p-2 w-full h-14  rounded-md border-2 border-bg-gray focus:outline-none mb-2"
        />
        <div className=" font-medium mb-1">Пароль</div>
        <input
          type="text"
          placeholder="Напишите пароль"
          {...register("password")}
          id=""
          className="p-2 w-full h-14  rounded-md border-2 border-bg-gray focus:outline-none mb-2"
        />
        <button
          type="submit"
          value="submit"
          className=" bg-text-active rounded-lg text-base text-bg-white h-14 w-full mb-2"
        >
          Вход
        </button>
      </form>
      <div className="mx-2">
        <button
          onClick={() => dispatch(registeration())}
          className=" bg-text-black bg-opacity-10 text-text-active rounded-lg text-base h-14 w-full"
        >
          Нет аккаунта
        </button>
      </div>

      {error && (
        <div className=" mx-2 p-2 mt-2 text-text-error font-medium rounded-md border-2 border-text-error">
          Неверный логин или код
        </div>
      )}
    </>
  );
}
