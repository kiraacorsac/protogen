<script lang="ts">
  export let name;
  export let url;
  let button;

  async function requestAnimation() {
    let isOK = false;
    try {
      button.classList.add("gray-bg");
      let response = await fetch(`${url}/animation?name=${name}`);
      isOK = response.ok;
    } catch (error) {
      isOK = false;
    }
    if (isOK) {
      button.classList.add("green-bg");
      setTimeout(() => {
        button.classList.remove("green-bg");
        button.classList.remove("gray-bg");
      }, 500);
    } else {
      button.classList.add("red-bg");
      setTimeout(() => {
        button.classList.remove("red-bg");
        button.classList.remove("gray-bg");
      }, 500);
    }
  }
</script>

<button on:click={requestAnimation} bind:this={button}>
  {name}
</button>

<style>
</style>
