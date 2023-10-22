import { useForm } from "react-hook-form";
import { useMutation } from "react-query";
import axios from "axios";

import TagUI from "@/ui/tag/tag";

async function createProduct(data) {
  return axios.post("http://94.103.86.64:8080/api/newevent", data);
}

export default function AddEvents({ type }) {
  const { register, handleSubmit, reset } = useForm();

  const { error, mutate } = useMutation({
    mutationFn: (newProduct) => createProduct(newProduct),
    onSuccess: (data) => {
      router.push("/");
    },
  });

  const onSubmit = (data) => {
    const employee = {
      id: parseInt(localStorage.getItem("userId")),
      type: `${type === "беседы" ? "event" : "hobby"}`,
      subscribers: 0,
      begin_time: `${data.begin_d} ${data.begin_t}`,
      end_time: "",
      max_subscribers: parseInt(data.max_subscribers),
      name: data.name,
      description: data.description,
      tags: data.tags.split(",").map((obj) => ({"name": obj, "link": obj},)),
      image: "",
    };
    // alert(JSON.stringify(employee));
    mutate(JSON.stringify(employee));
    reset();
  };
  return (
    <>
      <form onSubmit={handleSubmit(onSubmit)} className="mx-2">
        <div className="">
          <div className="text-text-gray mx-4">Описание {type}</div>
          <div className=" bg-bg-white p-4">
            <div className="flex gap-2 mb-2">
              <div className=" bg-text-black h-20 w-20 rounded-full "></div>
              <div>
                <div className=" font-medium mb-1">Название {type}</div>
                <input
                  type="text"
                  placeholder="Название"
                  {...register("name")}
                  id=""
                  className="p-2 w-full  rounded-md border-2 border-bg-gray focus:outline-none"
                />
              </div>
            </div>
            <div className="mb-2">
              <div className=" font-medium mb-1">Описание {type}</div>
              <input
                type="text"
                placeholder="Описание"
                {...register("description")}
                id=""
                className="p-2 w-full  rounded-md border-2 border-bg-gray focus:outline-none"
              />
            </div>
            <div className="mb-2">
              <div className=" font-medium mb-1">
                Максимальное кол-во участников
              </div>
              <input
                type="number"
                placeholder="Количество"
                {...register("max_subscribers")}
                id=""
                className="p-2 w-full  rounded-md border-2 border-bg-gray focus:outline-none"
              />
            </div>
            <div className="flex gap-2 items-center">
              <input
                type="checkbox"
                id="scales"
                name="scales"
                className=" h-5 w-5"
              />
              <label for="scales" className=" text-base">
                Нужно подтверждение для участия в мероприятии
              </label>
            </div>
          </div>
        </div>
        <div className="">
          <div className="text-text-gray mx-4">Дата</div>
          <div className=" bg-bg-white p-4">
            <div className="flex gap-2 items-center mb-2">
              <input
                type="checkbox"
                id="scales"
                name="scales"
                className=" h-5 w-5"
              />
              <label for="scales" className=" text-base">
                Мероприятие многодневное?
              </label>
            </div>
            <div className="flex gap-2">
              <div className="">
                <div className=" font-medium mb-1">Дата</div>
                <input
                  type="text"
                  placeholder="Дата"
                  {...register("begin_d")}
                  subscribers
                  id=""
                  className="p-2 w-full  rounded-md border-2 border-bg-gray focus:outline-none"
                />
              </div>
              <div className="">
                <div className=" font-medium mb-1">Время</div>
                <input
                  type="text"
                  placeholder="Время"
                  {...register("begin_t")}
                  id=""
                  className="p-2 w-full  rounded-md border-2 border-bg-gray focus:outline-none"
                />
              </div>
            </div>
          </div>
        </div>
        <div className="">
          <div className="text-text-gray mx-4">Тэги</div>
          <div className=" bg-bg-white p-4">
            <div className="">
              <div className=" font-medium mb-1">Тэги</div>
              <div className=" inline-flex flex-wrap gap-2">
                <div className="flex w-fit p-1 rounded-md bg-text-active bg-opacity-20 text-text-tag">
                  <input type="checkbox" id="horns" name="horns" className="mr-2"/>
                    <label for="horns">Искусство</label>
  </div>
  <div className="flex w-fit p-1 rounded-md bg-text-active bg-opacity-20 text-text-tag">
    <input type="checkbox" id="it" name="it" className="mr-2"/>
    <label for="it">IT</label>
  </div>
  <div className="flex w-fit p-1 rounded-md bg-text-active bg-opacity-20 text-text-tag">
    <input type="checkbox" id="Sport" name="Sport" className="mr-2"/>
    <label for="Sport">Спорт</label>
  </div>
  <div className="flex w-fit p-1 rounded-md bg-text-active bg-opacity-20 text-text-tag">
    <input type="checkbox" id="Music" name="Music" className="mr-2"/>
    <label for="Music">Музыка</label>
  </div>
  <div className="flex w-fit p-1 rounded-md bg-text-active bg-opacity-20 text-text-tag">
    <input type="checkbox" id="Stand-up" name="Stand-up" className="mr-2"/>
    <label for="Stand-up">Stand-up</label>
  </div>
  <div className="flex w-fit p-1 rounded-md bg-text-active bg-opacity-20 text-text-tag">
    <input type="checkbox" id="Fashion" name="Fashion" className="mr-2"/>
    <label for="Fashion">Мода</label>
  </div>
  <div className="flex w-fit p-1 rounded-md bg-text-active bg-opacity-20 text-text-tag">
    <input type="checkbox" id="anime" name="anime" className="mr-2"/>
    <label for="anime">Аниме</label>
  </div>
  <div className="flex w-fit p-1 rounded-md bg-text-active bg-opacity-20 text-text-tag">
    <input type="checkbox" id="books" name="books" className="mr-2"/>
    <label for="books">Книги</label>
  </div>
  <div className="flex w-fit p-1 rounded-md bg-text-active bg-opacity-20 text-text-tag">
    <input type="checkbox" id="nature" name="nature" className="mr-2"/>
    <label for="nature">Природа</label>
  </div></div>
              
              {/* <input
                type="text"
                placeholder="Тэг"
                {...register("tags")}
                id=""
                className="p-2 w-full  rounded-md border-2 border-bg-gray focus:outline-none mb-2"
              />
              <div className="flex gap-1">
                <div className=" text-sm text-text-gray">Например:</div>
                <TagUI text="Хакатон" />
                <TagUI text="Онлайн" />
                <TagUI text="Образование" />
                <TagUI text="IT" />
              </div> */}
            </div>
          </div>
        </div>
        <div className="mx-4">
          <button
            type="submit"
            value="submit"
            className=" bg-text-active rounded-lg text-base text-bg-white h-16 w-full"
          >
            Создать
          </button>
        </div>
      </form>
    </>
  );
}
