export const mutation = useMutation({
  mutationFn: (newTodo) => {
    return axios.post("/todos", newTodo);
  },
});
