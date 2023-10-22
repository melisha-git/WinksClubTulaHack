import { useSelector } from "react-redux";

import MainSection from "./main";
import Navigation from "./navigation";
import Search from "./search";

export default function Header() {
  const value = useSelector((state) => state.searchElement.value);
  return (
    <>
      {value ? <Search /> : <MainSection />}
      <Navigation />
    </>
  );
}
