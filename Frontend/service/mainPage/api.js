import axios from "axios";

//get recomendation chat
export async function getProduct() {
  const { data } = await axios.get("http://94.103.86.64:8080/allevents");
  return data;
}

//get favorite chat
export async function getFavoriteProduct() {
  const params = {
    id: localStorage.getItem("userId"),
  };
  const { data } = await axios.get("http://94.103.86.64:8080/api/events", {
    params,
  });
  return data;
}
