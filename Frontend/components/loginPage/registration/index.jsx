"use client";
import { useForm } from "react-hook-form";
import { useDispatch } from "react-redux";
import { codeVerify, login } from "@/redux/slices/loginElementSlice";

export default function Registration() {
  const { register, handleSubmit } = useForm();
  const dispatch = useDispatch();
  const onSubmit = (data) => {
    if (
      JSON.stringify(data.password) === JSON.stringify(data.retype_password)
    ) {
      // alert(JSON.stringify(data));
      localStorage.setItem("login", data.login);
      localStorage.setItem("password", data.password);
      dispatch(codeVerify());
    } else alert("У вас разные пароли");
  };
  return (
    <>
      <div className="text-center text-2xl text-text-active font-bold">
        Регистрация
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
          placeholder="Придумайте пароль"
          {...register("password")}
          id=""
          className="p-2 w-full h-14  rounded-md border-2 border-bg-gray focus:outline-none mb-2"
        />
        <div className=" font-medium mb-1">Повторите пароль</div>
        <input
          type="text"
          placeholder="Повторите пароль"
          {...register("retype_password")}
          id=""
          className="p-2 w-full h-14 rounded-md border-2 border-bg-gray focus:outline-none mb-2"
        />

        <button
          type="submit"
          value="submit"
          className=" bg-text-active rounded-lg text-base text-bg-white h-14 w-full mb-2"
        >
          Создать
        </button>
      </form>
      <button
        onClick={() => dispatch(login())}
        className=" bg-text-black bg-opacity-10 text-text-active rounded-lg text-base h-14 w-full"
      >
        Есть аккаунт
      </button>
    </>
  );
}
